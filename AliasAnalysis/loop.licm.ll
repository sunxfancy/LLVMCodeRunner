; ModuleID = 'loop.ll'
source_filename = "loop.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@data = global [1000 x [1000 x double]] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define void @_Z3mulPA1000_d([1000 x double]* %a) #0 {
  %1 = alloca [1000 x double]*, align 8
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store [1000 x double]* %a, [1000 x double]** %1, align 8
  store i32 0, i32* %i, align 4
  %2 = load [1000 x double]*, [1000 x double]** %1, align 8
  %3 = load [1000 x double]*, [1000 x double]** %1, align 8
  %j.promoted1 = load i32, i32* %j, align 1
  %i.promoted = load i32, i32* %i, align 1
  br label %4

; <label>:4:                                      ; preds = %25, %0
  %5 = phi i32 [ %26, %25 ], [ %i.promoted, %0 ]
  %.lcssa2 = phi i32 [ %.lcssa, %25 ], [ %j.promoted1, %0 ]
  %6 = icmp slt i32 %5, 1000
  br i1 %6, label %7, label %27

; <label>:7:                                      ; preds = %4
  %8 = sext i32 %5 to i64
  %9 = sext i32 %5 to i64
  br label %10

; <label>:10:                                     ; preds = %22, %7
  %11 = phi i32 [ %23, %22 ], [ 0, %7 ]
  %12 = icmp slt i32 %11, 1000
  br i1 %12, label %13, label %24

; <label>:13:                                     ; preds = %10
  %14 = sext i32 %11 to i64
  %15 = getelementptr inbounds [1000 x double], [1000 x double]* %2, i64 %14
  %16 = getelementptr inbounds [1000 x double], [1000 x double]* %15, i64 0, i64 %8
  %17 = load double, double* %16, align 8
  %18 = fmul double %17, 1.000000e-02
  %19 = sext i32 %11 to i64
  %20 = getelementptr inbounds [1000 x double], [1000 x double]* %3, i64 %19
  %21 = getelementptr inbounds [1000 x double], [1000 x double]* %20, i64 0, i64 %9
  store double %18, double* %21, align 8
  br label %22

; <label>:22:                                     ; preds = %13
  %23 = add nsw i32 %11, 1
  br label %10

; <label>:24:                                     ; preds = %10
  %.lcssa = phi i32 [ %11, %10 ]
  br label %25

; <label>:25:                                     ; preds = %24
  %26 = add nsw i32 %5, 1
  br label %4

; <label>:27:                                     ; preds = %4
  %.lcssa3 = phi i32 [ %5, %4 ]
  %.lcssa2.lcssa = phi i32 [ %.lcssa2, %4 ]
  store i32 %.lcssa2.lcssa, i32* %j, align 1
  store i32 %.lcssa3, i32* %i, align 1
  ret void
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
