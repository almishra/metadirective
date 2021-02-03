// RUN: %clang_cc1 -verify -fopenmp -x c++ -std=c++14 -emit-llvm %s -o - | FileCheck %s
// expected-no-diagnostics
#define N 1000
void func() {
  // Test where a valid when clause contains empty directive.
  // The directive will be ignored and code for a serial for loop will be generated.
#pragma omp metadirective when(implementation = {vendor(llvm)} \
                               :) default(parallel for)
  for (int i = 0; i < N; i++)
    ;
}

// CHECK: void @_Z4funcv() #0 {
// CHECK: entry:
// CHECK:   %i = alloca i32, align 4
// CHECK:   store i32 0, i32* %i, align 4
// CHECK:   br label %for.cond
// CHECK: for.cond:
// CHECK:   %0 = load i32, i32* %i, align 4
// CHECK:   %cmp = icmp slt i32 %0, 1000
// CHECK:   br i1 %cmp, label %for.body, label %for.end
// CHECK: for.body:
// CHECK:   br label %for.inc
// CHECK: for.inc:
// CHECK:   %1 = load i32, i32* %i, align 4
// CHECK:   %inc = add nsw i32 %1, 1
// CHECK:   store i32 %inc, i32* %i, align 4
// CHECK:   br label %for.cond, !llvm.loop !2
// CHECK: for.end:
// CHECK:   ret void
// CHECK: }
