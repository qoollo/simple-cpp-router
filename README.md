# Simple C++ URI routing library

## Requirements
C++11 compiler with regex support

## Example usage

```cpp

    Router router;
    
    router.registerPath("/simple_path");
    router.registerPath("/one/two");
    router.registerPath("/path/with/:dynamic_var");
    router.registerPath("/path/to/:one_var/and/:another_var");
    
    PathMatch match = router.matchPath("/path/to/dynvar_1/and/dynvar_2");
    
    assert(match.pathTemplate() == "/path/to/:one_var/and/:another_var");
    assert(std::string("dynvar_1") == match.getVar("one_var"));
    assert(std::string("dynvar_2") == match.getVar("another_var"));
    
```
