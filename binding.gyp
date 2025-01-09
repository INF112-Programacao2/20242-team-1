{
  "targets": [
    {
      "target_name": "myclass",
      "sources": ["./integration/myclass.cpp"],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include_dir\")",
        
      ],
      "cflags": ["-std=c++17"],
      "cflags_cc!": ["-fno-exceptions"],  
      "defines": ["NODE_ADDON_API_CPP_EXCEPTIONS"],
       "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],   
    }
  ]
}
