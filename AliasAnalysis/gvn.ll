; ModuleID = 'main.ll'
source_filename = "main.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define i32 @test1(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %d = alloca i32, align 4
  %c = alloca i32*, align 8
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  store i32* %d, i32** %c, align 8
  %3 = add nsw i32 %a, %b
  store i32 %3, i32* %d, align 4
  store i32 3, i32* %d, align 4
  ret i32 3
}

; Function Attrs: noinline nounwind uwtable
define i32 @test2(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %e = alloca i32, align 4
  %f = alloca i32, align 4
  %c = alloca i32*, align 8
  %d = alloca i32*, align 8
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  store i32* %1, i32** %c, align 8
  store i32* %1, i32** %d, align 8
  %3 = add nsw i32 %a, %b
  store i32 %3, i32* %e, align 4
  store i32 %3, i32* %f, align 4
  ret i32 %3
}

; Function Attrs: nounwind uwtable
define i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @test1(i32 1, i32 2)
  %3 = call i32 @test2(i32 2, i32 3)
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
