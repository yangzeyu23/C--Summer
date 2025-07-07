#include <iostream>
#include <vector>
using namespace std;

//  空类，用于指代响应者对象
class Empty  {  };

//  事件响应者类模板，保存特定事件的响应者与响应行为
template< typename EventAction >  class EventResponsor
{
public:
  EventResponsor() : actor(NULL),  action(NULL)  {  }
  EventResponsor( Empty * actor, EventAction * action ) : actor(actor),  action(action)  {  }
  
  friend  bool operator==( const EventResponsor & lhs, const EventResponsor & rhs )
  {  return lhs.actor == rhs.actor && *lhs.action == *rhs.action; }
  
public:    //  公开的数据成员，以方便使用者
  Empty * actor;
  EventAction * action;
};    //  template<typename EventAction> class EventResponsor


//  事件类模板，用于管理特定事件的所有响应者
template< typename EventAction >  class Event
{
public:
  typedef vector<EventResponsor<EventAction> > EventResponsors;
  typedef typename vector<EventResponsor<EventAction> >::iterator EventIterator;

public:
  virtual ~Event()
  {
    for( EventIterator it = this->_ers.begin();  it != this->_ers.end(); ++it )
    {
      delete it->action,  it->action = NULL;
    }
  }

  EventResponsors & GetResponsors()  {  return this->_ers;  }


  //  事件绑定，将实际响应者和响应行为挂接到事件响应者对象上
  template< typename Responsor, typename Action >
  void Bind( Responsor * actor, Action action )
  {
    Action * act = new Action( action );
    EventResponsor<EventAction> er( (Empty*)actor, (EventAction*)act );
    bool unbound = true;
    for( EventIterator it = this->_ers.begin(); it != this->_ers.end(); ++it )
    {
      if( *it == er )    //  发现重复的事件响应者，说明已绑定
      {
        unbound = false;  break;
      }
    }
    if( unbound )
      this->_ers.push_back( er );
    else
      delete er.action,  er.action = NULL;
  }


//  解除事件绑定，删除事件响应者对象
  template< typename Responsor, typename Action >
  void Unbind( Responsor * actor, Action action )
  {
    Action * act = new Action( action );
    EventResponsor<EventAction> er( (Empty*)actor, (EventAction*)act );
    for( EventIterator it = this->_ers.begin(); it != this->_ers.end(); ++it )
    {
      if( *it == er )    //  找到待删除的事件响应者对象
      {
        delete it->action, this->_ers.erase( it );  break;
      }
    }
    delete er.action,  er.action = NULL;
  }

private:
  EventResponsors _ers;
};    //  template<typename EventAction> class Event

//  定义事件委托模型、指向类成员函数的指针
typedef Empty EventDelegator;
typedef void ( EventDelegator::*ValueChanged )( int value, void * tag );

//  触发者
class Trigger
{
public:
  Trigger() : _value(0)  {  }
  void SetValue( int value, void * tag );
  int GetValue()  {  return _value;  }
public:
  //  值变化事件，公开属性，方便在类外设定
  Event<ValueChanged>  value_changed;
private:
  int  _value;
};

//  设定值，遍历特定事件的响应对象列表，逐一触发值变更事件
void Trigger::SetValue( int value, void * tag )
{
  if( _value == value )
    return;
  _value = value;
  Event<ValueChanged>::EventResponsors  ers;
  ers = this->value_changed.GetResponsors();
  if( !ers.empty() )
  {
    Event<ValueChanged>::EventIterator  it;
    for( it = ers.begin(); it != ers.end(); ++it )
    {
      ( ( it->actor )->*( *( it->action ) ) )( value, tag );    //  响应事件
    }
  }
}

//  行动者
class Actor
{
public:
  //  侦听事件，绑定本对象的事件响应函数到侦听的事件
  void Listen( Trigger * trigger )
  {  trigger->value_changed.Bind( this, &Actor::OnValueChanged );  }

  //  停止侦听，从侦听的事件中取消绑定本对象的事件响应活动
  void Unlisten( Trigger * trigger )
  {  trigger->value_changed.Unbind( this, &Actor::OnValueChanged );  }

  //  值变更事件的响应函数
  void OnValueChanged( int value, void * tag )
  {  cout << reinterpret_cast<char*>(tag) << value << "." << endl;  }
};


int main()
{
  const char * s = "Now the value is ";
  Trigger t;
  Actor a1, a2;

  a1.Listen( &t );
  a2.Listen( &t );

  cout << "Listening..."  << endl;
  t.SetValue( 10, reinterpret_cast<void*>( const_cast<char*>(s) ) );

  a2.Unlisten( &t );
  cout << "Listening again..."  << endl;
  t.SetValue( 20, reinterpret_cast<void*>( const_cast<char*>(s) ) );

  return 0;
}
