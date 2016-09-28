{
  "targets": [
    {
      "target_name": "optimus",
      "sources": [ "optimus.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
