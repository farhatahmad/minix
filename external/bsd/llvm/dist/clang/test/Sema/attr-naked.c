// RUN: %clang_cc1 %s -verify -fsyntax-only -triple i686-pc-linux

int a __attribute__((naked)); // expected-warning {{'naked' attribute only applies to functions}}

__attribute__((naked)) int t0(void) {
  __asm__ volatile("mov r0, #0");
}

void t1() __attribute__((naked));

void t2() __attribute__((naked(2))); // expected-error {{'naked' attribute takes no arguments}}

__attribute__((naked)) int t3() { // expected-note{{attribute is here}}
  return 42; // expected-error{{non-ASM statement in naked function is not supported}}
}

__attribute__((naked)) int t4() {
  asm("movl $42, %eax");
  asm("retl");
}

__attribute__((naked)) int t5(int x) {
  asm("movl x, %eax");
  asm("retl");
}

__attribute__((naked)) void t6() {
  ;
}

__attribute__((naked)) void t7() {
  asm("movl $42, %eax");
  ;
}

extern int x, y;

__attribute__((naked)) void t8(int z) { // expected-note{{attribute is here}}
  __asm__ ("movl $42, %1"
           : "=r"(x),
             "=r"(z) // expected-error{{parameter references not allowed in naked functions}}
           );
}

__attribute__((naked)) void t9(int z) { // expected-note{{attribute is here}}
  __asm__ ("movl %eax, %1"
           : : "r"(x),
               "r"(z) // expected-error{{parameter references not allowed in naked functions}}
           );
}
