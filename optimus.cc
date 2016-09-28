#include <v8-profiler.h>
#include <nan.h>
#include <iostream>

double toMillisecond(int64_t sample) {
  return 0.001f * static_cast<double>(sample);
}

template <typename Node>
v8::Local<v8::Object> ReadNodeProfile(Node& node){
  auto jobject = Nan::New<v8::Object>();

  jobject->Set( Nan::New("name").ToLocalChecked(),
                    node->GetFunctionName() );

  jobject->Set( Nan::New("line").ToLocalChecked(),
                    Nan::New(node->GetLineNumber()) );

  jobject->Set( Nan::New("column").ToLocalChecked(),
                    Nan::New(node->GetLineNumber()) );

  jobject->Set( Nan::New("bailout").ToLocalChecked(),
                    Nan::New(node->GetBailoutReason()).ToLocalChecked() );

  return jobject;
}


template <typename FExtractor, typename Profile>
v8::Local<v8::Array> GetProfile(FExtractor& extractor, Profile& profile, int amount){

  auto list = Nan::New<v8::Array>(amount);

  for(int index = 0; index < amount; index++) {
    auto node = profile->GetSample(index);

    list->Set(index, extractor(node));
  }

  return list;
}


template <typename T>
v8::Local<v8::Object> CPUProfToV8Object(T& profile) {
  auto object = Nan::New<v8::Object>();
  int sampleCount = profile->GetSamplesCount();

  object->Set(Nan::New("title").ToLocalChecked(), profile->GetTitle() );

  object->Set(Nan::New("samples_count").ToLocalChecked(), Nan::New(sampleCount) );

  auto list = GetProfile(ReadNodeProfile<const v8::CpuProfileNode*>, profile, sampleCount);

  object->Set(Nan::New("profile").ToLocalChecked(), list );

  //cleaning up.
  profile->Delete();

  return object;
}


void StartCPUProfiling(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  auto cpu_profiler = Nan::GetCurrentContext()->GetIsolate()->GetCpuProfiler();
  cpu_profiler->StartProfiling((args.Length() > 0)
      ? args[0].As<v8::String>()
      : v8::String::Empty(args.GetIsolate()), true);
}

void StopCPUProfiling(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  auto cpu_profiler = args.GetIsolate()->GetCpuProfiler();
  //last_profile =
  auto profile = cpu_profiler->StopProfiling((args.Length() > 0)
      ? args[0].As<v8::String>()
      : v8::String::Empty(args.GetIsolate()));

    args.GetReturnValue().Set(  CPUProfToV8Object(profile) );
}

void GetGCInformation(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    v8::HeapStatistics heap_stats;

    std::cout << "getting gc information" << std::endl;

    Nan::GetCurrentContext()->GetIsolate()->GetHeapStatistics(&heap_stats);

    std::cout << "getting gc information: ok" << std::endl;

    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    obj->Set(Nan::New("total_heap_size").ToLocalChecked(), Nan::New(static_cast<double>(heap_stats.total_heap_size())) );
    obj->Set(Nan::New("total_heap_size_executable").ToLocalChecked(), Nan::New(static_cast<double>(heap_stats.total_heap_size_executable())) );
    obj->Set(Nan::New("total_physical_size").ToLocalChecked(), Nan::New(static_cast<double>(heap_stats.total_physical_size())) );
    obj->Set(Nan::New("used_heap_size").ToLocalChecked(), Nan::New(static_cast<double>(heap_stats.used_heap_size())) );
    obj->Set(Nan::New("heap_size_limit").ToLocalChecked(), Nan::New(static_cast<double>(heap_stats.heap_size_limit())) );

    info.GetReturnValue().Set(obj);
}

void Init(v8::Local<v8::Object> exports) {

  exports->Set(Nan::New("start_cpu").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(StartCPUProfiling)->GetFunction());

  exports->Set(Nan::New("stop_cpu").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(StopCPUProfiling)->GetFunction());

  exports->Set(Nan::New("gc").ToLocalChecked(),
              Nan::New<v8::FunctionTemplate>(GetGCInformation)->GetFunction());
}

NODE_MODULE(optimus, Init)
