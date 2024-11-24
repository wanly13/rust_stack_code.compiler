cmake_minimum_required(VERSION 3.25)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)


#add_executable(untitled1 svm.cpp svm_parser.cpp svm_run.cpp)
add_executable(untitled1 exp.cpp
      parser.cpp environment.hh imp_codegen.cpp  imp_type_checker.cpp
     scanner.cpp token.cpp  visitor.cpp main.cpp imp_type.cpp imp_interpreter.cpp
   imp_value.cpp imp_value_visitor.hh)


#-- Genera la maquina de pila , genera el archivo input1.txt.sm
#   g++ -o calc1 exp.cpp parser.cpp environment.hh imp_codegen.cpp imp_type_checker.cpp  scanner.cpp token.cpp visitor.cpp main.cpp imp_type.cpp imp_interpreter.cpp   imp_value.cpp imp_value_visitor.hh
#   ./calc1.exe "input1.txt"

#-- Lee la maquina de pila(el archivo input1.txt.sm) y da el resultado de esa maquina 
#   g++ -o calc2 svm.cpp svm_parser.cpp svm_run.cpp
#   ./calc2.exe "input1.txt.sm"