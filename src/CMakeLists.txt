cmake_minimum_required(VERSION 2.8)
project(routing)

include_directories(src)

add_library(routing SHARED
    Routing/Router.cpp Routing/Router.h
    Routing/PathMatch.cpp Routing/PathMatch.h
    Routing/Exceptions.h

    Routing/Details/PathTemplate.cpp Routing/Details/PathTemplate.h
    Routing/Details/RegexConverter.cpp Routing/Details/RegexConverter.h
    Routing/Details/PathTemplateParser.cpp Routing/Details/PathTemplateParser.h
    Routing/Details/StringTokenizer.cpp Routing/Details/StringTokenizer.h
)
