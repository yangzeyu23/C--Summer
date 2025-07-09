// common.cpp
#include "common.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

// Function to trim whitespace from a string
char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null terminate after the last non-space character
    *(end + 1) = '\0';

    return str;
}

// Function to split a string by a delimiter
char** split_string(const char* str, const char* delimiter, int* count) {
    char* temp_str = strdup(str);
    char* token;
    char** result = nullptr;
    *count = 0;

    token = strtok(temp_str, delimiter);
    while (token != nullptr) {
        result = (char**)realloc(result, sizeof(char*) * (*count + 1));
        result[*count] = strdup(token);
        (*count)++;
        token = strtok(nullptr, delimiter);
    }

    free(temp_str);
    return result;
}

// Function to free the memory allocated for the split string
void free_split_string(char** split_str, int count) {
    for (int i = 0; i < count; i++) {
        free(split_str[i]);
    }
    free(split_str);
}

void log_message(const char* message) {
    std::cout << "[LOG]: " << message << std::endl;
}

void error_message(const char* message) {
    std::cerr << "[ERROR]: " << message << std::endl;
}