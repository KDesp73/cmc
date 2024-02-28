#include "logging.h"
#include <iostream>
using namespace std;

void LOG(string status, string message){
	cout << '[' + status + "] " << message << endl;
}
void INFO(string message){
	LOG("INFO", message);
}
void WARN(string message){
	LOG("WARN", message);
}
void ERRO(string message){
	LOG("ERRO", message);
}
void DEBU(string message){
	LOG("DEBU", message);
}
