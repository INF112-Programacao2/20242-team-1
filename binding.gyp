{
  "targets": [
    {
      "target_name": "addon",
      "sources":  [
        "./integration/addon.cpp",
        "./api/DAO/DatabaseConnection.cpp",
        "./api/deck.cpp",
        "./api/DAO/deckdao.cpp",
        "./api/card.cpp"
      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include_dir\")",
        
      ],
      "libraries": ["/usr/lib/libsqlite3.so"],
      "cflags": ["-std=c++17"],
      "cflags_cc!": ["-fno-exceptions"],  
      "defines": ["NODE_ADDON_API_CPP_EXCEPTIONS"],
       "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],   
    }
  ]
}
