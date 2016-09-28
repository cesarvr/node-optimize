# node-optimus 


This module give you access to V8 Profiling capabilities, it can be useful to check real-time telemetry. 


## Temeletry 

- Garbage collection information. 
- Crankshaft bailout information. (*telling you [why V8 compiler](https://github.com/vhf/v8-bailout-reasons) give up in trying optimize your function.*)

## Functions 

- gc
  - just information about the state of the garbage collection.

- start_cpu_profile/stop_cpu_profile
  - tell V8 to start recolecting information about the current execution. 


## Example 
``` javascript

optm.start_cpu_profile('profiling-1');    //tell V8 to start taking sample.

const MAX_SAMPLE = 1;

function create_random_vec3(size) {
  var sample = [];
  var rnd = (x) => Math.floor(Math.random() * x) + 1;

  for(var i=0; i<size; i++)
   sample.push({ x:rnd(size), y:rnd(size), z:rnd(size)  });

  return sample
};

var sample = create_random_vec3(MAX_SAMPLE);

console.log('vec3->', sample);
console.log('prof->', optm.stop_cpu_profile('profiling-1'));   // tell V8 to stop.

```


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



