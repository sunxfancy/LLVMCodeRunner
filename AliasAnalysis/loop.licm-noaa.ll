; ModuleID = 'loop.ll'
source_filename = "loop.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@data = common global [1000 x [1000 x double]] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define void @mul([1000 x double]* %a) #0 {
  %1 = alloca [1000 x double]*, align 8
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store [1000 x double]* %a, [1000 x double]** %1, align 8
  store i32 0, i32* %i, align 4
  br label %2

; <label>:2:                                      ; preds = %30, %0
  %3 = load i32, i32* %i, align 4
  %4 = icmp slt i32 %3, 1000
  br i1 %4, label %5, label %33

; <label>:5:                                      ; preds = %2
  store i32 0, i32* %j, align 4
  br label %6

; <label>:6:                                      ; preds = %26, %5
  %7 = load i32, i32* %j, align 4
  %8 = icmp slt i32 %7, 1000
  br i1 %8, label %9, label %29

; <label>:9:                                      ; preds = %6
  %10 = load i32, i32* %i, align 4
  %11 = sext i32 %10 to i64
  %12 = load i32, i32* %j, align 4
  %13 = sext i32 %12 to i64
  %14 = load [1000 x double]*, [1000 x double]** %1, align 8
  %15 = getelementptr inbounds [1000 x double], [1000 x double]* %14, i64 %13
  %16 = getelementptr inbounds [1000 x double], [1000 x double]* %15, i64 0, i64 %11
  %17 = load double, double* %16, align 8
  %18 = fmul double %17, 1.000000e-02
  %19 = load i32, i32* %i, align 4
  %20 = sext i32 %19 to i64
  %21 = load i32, i32* %j, align 4
  %22 = sext i32 %21 to i64
  %23 = load [1000 x double]*, [1000 x double]** %1, align 8
  %24 = getelementptr inbounds [1000 x double], [1000 x double]* %23, i64 %22
  %25 = getelementptr inbounds [1000 x double], [1000 x double]* %24, i64 0, i64 %20
  store double %18, double* %25, align 8
  br label %26

; <label>:26:                                     ; preds = %9
  %27 = load i32, i32* %j, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %j, align 4
  br label %6

; <label>:29:                                     ; preds = %6
  br label %30

; <label>:30:                                     ; preds = %29
  %31 = load i32, i32* %i, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, i32* %i, align 4
  br label %2

; <label>:33:                                     ; preds = %2
  ret void
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @mul([1000 x double]* getelementptr inbounds ([1000 x [1000 x double]], [1000 x [1000 x double]]* @data, i32 0, i32 0))
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
