'use strict';
var optm = require('./build/Release/optimus');

function de_optimized(x,y){
  try{
    var add = x+y;
    throw "Boom!";
  }catch(e){
      console.log('De-OptimizeMe');
  }
}


// strict & sloppy modes
function test2() {
  var _arguments = arguments;
  for (var i = 0; i < 1; i++) {
    _arguments = [0]; // Unsupported phi use of arguments
  }
} 

optm.start_cpu_profile('profiling-1');

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
console.log('prof->', optm.stop_cpu_profile('profiling-1'));



optm.start_cpu_profile('deoptm')
de_optimized()
console.log('testing de-optimize function ->', optm.stop_cpu_profile('deoptm'));



optm.start_cpu_profile('deoptm-2')
test2();
console.log('testing deoptm-2 function ->', optm.stop_cpu_profile('deoptm-2'));


console.log('-----Garbage Collection-----')
console.log('----------------------------')
console.log('read->', optm.gc());
console.log('----------------------------')

