# CPU and Process Information Project

This project is designed to retrieve and display detailed information about the CPU and running processes on a Linux system. It serves as a foundational component for a web server project.

## Project Structure

```
cpu-process-info
├── src
│   ├── main.cpp          # Entry point of the program
│   ├── cpu_info.cpp      # Implementation of CPU information retrieval
│   ├── cpu_info.h        # Header file for CPU information functions
│   ├── process_info.cpp   # Implementation of process information retrieval
│   ├── process_info.h     # Header file for process information functions
├── Makefile              # Build instructions for the project
└── README.md             # Documentation for the project
```

## Features

- **CPU Information**: The program reads from `/proc/cpuinfo` to gather detailed information about the CPU, including the number of processors, model name, CPU speed, and cache size.
  
- **Process Information**: The program scans the `/proc` directory to retrieve and display information about all running processes, including their PID, name, state, and memory usage.

## Usage

1. **Build the Project**: Navigate to the project directory and run the following command to compile the program:
   ```
   make
   ```

2. **Run the Program**: After building, execute the program with:
   ```
   ./cpu-process-info
   ```

## Requirements

- This project is intended to run on a Linux environment (e.g., WSL).
- Ensure that you have the necessary permissions to read from the `/proc` filesystem.

## Contribution

Feel free to contribute to this project by adding more features or improving the existing code. Please ensure that your contributions adhere to the project's coding standards and documentation practices.