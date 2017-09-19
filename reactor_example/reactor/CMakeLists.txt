add_library (reactor reactor.cpp ConcreteReactor.cpp SelectReactorImpl.cpp 
    DemuxTable.cpp LogEventAcceptor.cpp LogEventHandler.cpp 
    SocketAcceptor.cpp SocketStream.cpp EventType.cpp)
target_include_directories (reactor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})