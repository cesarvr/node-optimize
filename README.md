# node-optimus 


This module give you access to V8 Profiling capabilities, it can be useful to check real-time telemetry. 


## Temeletry 

- Garbage collection information. 
- Optimization and Bail-out information. (*for some the V8 Optimizer give up with your function*)



```
{ title: 'deoptm',

profile:

samples_count: 2 
[ 
   { name: '', line: 0, column: 0, bailout: '', script: '' },
   { name: 'writeUtf8String', line: 0, column: 0, bailout: '', script: '' } i
], 

}

-----Garbage Collection-----
----------------------------
read-> { total_heap_size: 11530240,
total_heap_size_executable: 5242880,
total_physical_size: 7149000,
used_heap_size: 5349632,
heap_size_limit: 1535115264 }
----------------------------
```



