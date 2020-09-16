// RUN: %clang_cc1 -verify -fopenmp -emit-llvm %s -o - | FileCheck %s
// expected-no-diagnostics

int main(int argc, char **argv) {
  int N = 15;
#pragma omp metadirective when(user = {condition(N <= 1)} \
                               : parallel)                \
    when(user = {condition(N > 10)}                       \
         : parallel for)
  for (int i = 0; i < N; i++)
    ;
  // CHECK: %cmp{{[0-9]*}} = icmp sle i32 %{{[0-9]+}}, 1
  // CHECK: br i1 %cmp{{[0-9]*}}, label %if.then{{[0-9]*}}, label %if.else{{[0-9]*}}
  // CHECK: if.then{{[0-9]*}}:
  // CHECK: call {{.*}}void (%struct.ident_t*, i32, void (i32*, i32*, ...)*, ...) @__kmpc_fork_call(%struct.ident_t* @0, i32 1, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i32*)* [[OMP_OUTLINED:@.+]] to void (i32*, i32*, ...)*), i32* %N)
  // CHECK: br label %if.end{{[0-9]*}}
  // CHECK: if.else{{[0-9]*}}:
  // CHECK: %{{[0-9]+}} = load i32, i32* %N, align 4
  // CHECK: %cmp{{[0-9]+}} = icmp sgt i32 %{{[0-9]+}}, 10
  // CHECK: br i1 %cmp{{[0-9]*}}, label %if.then{{[0-9]*}}, label %if.end{{[0-9]*}}
  // CHECK: if.then{{[0-9]*}}:
  // CHECK: call {{.*}}void (%struct.ident_t*, i32, void (i32*, i32*, ...)*, ...) @__kmpc_fork_call(%struct.ident_t* @0, i32 1, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i32*)* [[OMP_OUTLINED:@.+]] to void (i32*, i32*, ...)*), i32* %N)
  // CHECK: br label %if.end
  // CHECK: if.end{{[0-9]*}}:
  // CHECK: br label %if.end{{[0-9]*}}
  // CHECK: if.end{{[0-9]*}}:
  // CHECK: ret i32 0

  return 0;
}
// CHECK: define internal void [[OMP_OUTLINED:@.*]](i32* noalias %.global_tid., i32* noalias %.bound_tid., i32* nonnull align 4 dereferenceable(4) %N)
// CHECK: declare !callback !{{[0-9]+}} void @__kmpc_fork_call(%struct.ident_t*, i32, void (i32*, i32*, ...)*, ...)
// CHECK: define internal void [[OMP_OUTLINED:@.+]](i32* noalias %.global_tid., i32* noalias %.bound_tid., i32* nonnull align 4 dereferenceable(4) %N)
// CHECK: declare void @__kmpc_for_static_init_4(%struct.ident_t*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)
// CHECK: declare void @__kmpc_for_static_fini(%struct.ident_t*, i32)
