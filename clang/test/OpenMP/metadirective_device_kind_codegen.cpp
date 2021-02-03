// RUN: %clang_cc1 -verify -fopenmp -x c++ -std=c++14 -emit-llvm %s -o - | FileCheck %s
// RUN: %clang_cc1 -verify -fopenmp -x c++ -triple x86_64-unknown-linux -emit-llvm %s -fexceptions -fcxx-exceptions -o - -fsanitize-address-use-after-scope | FileCheck %s
// RUN: %clang_cc1 -verify -fopenmp -x c++ -triple aarch64-unknown-linux -emit-llvm %s -fexceptions -fcxx-exceptions -o - -fsanitize-address-use-after-scope | FileCheck %s
// RUN: %clang_cc1 -verify -fopenmp -x c++ -triple ppc64le-unknown-linux -emit-llvm %s -fexceptions -fcxx-exceptions -o - -fsanitize-address-use-after-scope | FileCheck %s

// expected-no-diagnostics

void bar();

void foo() {
#pragma omp metadirective when(device = {kind(any)} \
                               : parallel)
  bar();
#pragma omp metadirective when(device = {kind(host, cpu)} \
                               : parallel for num_threads(4))
  for (int i = 0; i < 100; i++)
    ;
#pragma omp metadirective when(device = {kind(host)} \
                               : parallel for)
  for (int i = 0; i < 100; i++)
    ;
#pragma omp metadirective when(device = {kind(nohost, gpu)} \
                               :) when(device = {kind(cpu)} \
                                       : parallel)
  bar();
#pragma omp metadirective when(device = {kind(any, cpu)} \
                               : parallel)
  bar();
#pragma omp metadirective when(device = {kind(any, host)} \
                               : parallel)
  bar();
#pragma omp metadirective when(device = {kind(gpu)} \
                               : target parallel for) default(parallel for)
  for (int i = 0; i < 100; i++)
    ;
}

// CHECK: void @_Z3foov()
// CHECK: ...) @__kmpc_fork_call(
// CHECK-NEXT: @__kmpc_push_num_threads
// CHECK-COUNT-6: ...) @__kmpc_fork_call(
// CHECK: ret void

// CHECK: define internal void @.omp_outlined.(
// CHECK: void @_Z3barv()
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..1(
// CHECK: call void @__kmpc_for_static_init
// CHECK: call void @__kmpc_for_static_fini
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..2(
// CHECK: call void @__kmpc_for_static_init
// CHECK: call void @__kmpc_for_static_fini
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..3(
// CHECK: void @_Z3barv()
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..4(
// CHECK: void @_Z3barv()
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..5(
// CHECK: void @_Z3barv()
// CHECK: ret void

// CHECK: define internal void @.omp_outlined..6(
// CHECK: call void @__kmpc_for_static_init
// CHECK: call void @__kmpc_for_static_fini
// CHECK: ret void
