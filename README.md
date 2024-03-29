# Hold on!
This library is obsolete at this point and it might not even support the 2022 League Client at the moment. It could be a good learning resource though, so I've made it public : )

# LibLCU
C++ library that can control (or be) the League Client.

### What does it do?
LibLCU works like the UI process of the League Client (*LeagueClientUi*) to communicate with the back-end server process (*LeagueClient*). In simpler terms, you can use LibLCU to *be* the League Client.

### Dependencies
Depends on [*zstd*](https://github.com/facebook/zstd), [*libcurl*](https://github.com/curl/curl), [*websocketpp*](https://github.com/zaphoyd/websocketpp) and [*nlohmann-json*](https://github.com/nlohmann/json)

### Usage
LibLCU can be fully included into another C++ project or used as a static library. Please look at the [licenses](https://github.com/par0-git/LibLCU/blob/master/LICENSE) before use.

### How can I help?
Currently there is no code standards document for LibLCU, so please just follow these rules:
1. Use PascalCase for namespaces, classes, structs, functions
2. Use camelCase for objects and members
3. Use /// documentation for functions

Look at the issues page for things that need work.
Thanks!
