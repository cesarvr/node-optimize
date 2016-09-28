{
  "targets": [
    {
      "target_name": "optimus",
      "sources": [ "./lib/optimus.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
