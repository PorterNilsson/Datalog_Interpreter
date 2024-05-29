cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project("Datalog_Interpreter" VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} source/main.cpp 
source/AddAutomaton.h source/AddAutomaton.cpp
source/Automaton.h
source/ColonAutomaton.h source/ColonAutomaton.cpp
source/ColonDashAutomaton.h source/ColonDashAutomaton.cpp
source/CommaAutomaton.h source/CommaAutomaton.cpp
source/CommentAutomaton.h source/CommentAutomaton.cpp
source/Database.h source/Database.cpp
source/DatalogProgram.h source/DatalogProgram.cpp
source/FactsAutomaton.h source/FactsAutomaton.cpp
source/Graph.h source/Graph.cpp
source/Header.h source/Header.cpp
source/IdAutomaton.h source/IdAutomaton.cpp
source/Interpreter.h source/Interpreter.cpp
source/LeftParenAutomaton.h source/LeftParenAutomaton.cpp
source/Lexer.h source/Lexer.cpp
source/MultiCommentAutomaton.h source/MultiCommentAutomaton.cpp
source/MultiplyAutomaton.h source/MultiplyAutomaton.cpp
source/Parameter.h source/Parameter.cpp
source/Parser.h source/Parser.cpp
source/PeriodAutomaton.h source/PeriodAutomaton.cpp
source/Predicate.h source/Predicate.cpp
source/QueriesAutomaton.h source/QueriesAutomaton.cpp
source/QuestionMarkAutomaton.h source/QuestionMarkAutomaton.cpp
source/Relation.h source/Relation.cpp
source/RightParenAutomaton.h source/RightParenAutomaton.cpp
source/Rule.h source/Rule.cpp
source/RulesAutomaton.h source/RulesAutomaton.cpp
source/SchemesAutomaton.h source/SchemesAutomaton.cpp
source/StringAutomaton.h source/StringAutomaton.cpp
source/Token.h source/Token.cpp
source/Tuple.h source/Tuple.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
