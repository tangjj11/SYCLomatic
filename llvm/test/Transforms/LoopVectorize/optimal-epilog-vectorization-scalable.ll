; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; REQUIRES: asserts
; RUN: opt < %s  -passes='loop-vectorize' -force-target-supports-scalable-vectors=true -enable-epilogue-vectorization -epilogue-vectorization-force-VF=2 --debug-only=loop-vectorize -S -scalable-vectorization=on 2>&1 | FileCheck %s

target datalayout = "e-m:e-i64:64-n32:64-v256:256:256-v512:512:512"

; Currently we cannot handle scalable vectorization factors.
; CHECK: LV: Checking a loop in 'f1'
; CHECK: LEV: Epilogue vectorization factor is forced.
; CHECK: Epilogue Loop VF:2, Epilogue Loop UF:1

define void @f1(i8* %A) {
; CHECK-LABEL: @f1(
; CHECK-NEXT:  iter.check:
; CHECK-NEXT:    br i1 false, label [[VEC_EPILOG_SCALAR_PH:%.*]], label [[VECTOR_MAIN_LOOP_ITER_CHECK:%.*]]
; CHECK:       vector.main.loop.iter.check:
; CHECK-NEXT:    [[TMP0:%.*]] = call i64 @llvm.vscale.i64()
; CHECK-NEXT:    [[TMP1:%.*]] = mul i64 [[TMP0]], 4
; CHECK-NEXT:    [[MIN_ITERS_CHECK:%.*]] = icmp ult i64 1024, [[TMP1]]
; CHECK-NEXT:    br i1 [[MIN_ITERS_CHECK]], label [[VEC_EPILOG_PH:%.*]], label [[VECTOR_PH:%.*]]
; CHECK:       vector.ph:
; CHECK-NEXT:    [[TMP2:%.*]] = call i64 @llvm.vscale.i64()
; CHECK-NEXT:    [[TMP3:%.*]] = mul i64 [[TMP2]], 4
; CHECK-NEXT:    [[N_MOD_VF:%.*]] = urem i64 1024, [[TMP3]]
; CHECK-NEXT:    [[N_VEC:%.*]] = sub i64 1024, [[N_MOD_VF]]
; CHECK-NEXT:    br label [[VECTOR_BODY:%.*]]
; CHECK:       vector.body:
; CHECK-NEXT:    [[INDEX:%.*]] = phi i64 [ 0, [[VECTOR_PH]] ], [ [[INDEX_NEXT:%.*]], [[VECTOR_BODY]] ]
; CHECK-NEXT:    [[TMP4:%.*]] = add i64 [[INDEX]], 0
; CHECK-NEXT:    [[TMP5:%.*]] = getelementptr inbounds i8, i8* [[A:%.*]], i64 [[TMP4]]
; CHECK-NEXT:    [[TMP6:%.*]] = getelementptr inbounds i8, i8* [[TMP5]], i32 0
; CHECK-NEXT:    [[TMP7:%.*]] = bitcast i8* [[TMP6]] to <vscale x 4 x i8>*
; CHECK-NEXT:    store <vscale x 4 x i8> shufflevector (<vscale x 4 x i8> insertelement (<vscale x 4 x i8> poison, i8 1, i32 0), <vscale x 4 x i8> poison, <vscale x 4 x i32> zeroinitializer), <vscale x 4 x i8>* [[TMP7]], align 1
; CHECK-NEXT:    [[TMP8:%.*]] = call i64 @llvm.vscale.i64()
; CHECK-NEXT:    [[TMP9:%.*]] = mul i64 [[TMP8]], 4
; CHECK-NEXT:    [[INDEX_NEXT]] = add nuw i64 [[INDEX]], [[TMP9]]
; CHECK-NEXT:    [[TMP10:%.*]] = icmp eq i64 [[INDEX_NEXT]], [[N_VEC]]
; CHECK-NEXT:    br i1 [[TMP10]], label [[MIDDLE_BLOCK:%.*]], label [[VECTOR_BODY]], !llvm.loop [[LOOP0:![0-9]+]]
; CHECK:       middle.block:
; CHECK-NEXT:    [[CMP_N:%.*]] = icmp eq i64 1024, [[N_VEC]]
; CHECK-NEXT:    br i1 [[CMP_N]], label [[EXIT:%.*]], label [[VEC_EPILOG_ITER_CHECK:%.*]]
; CHECK:       vec.epilog.iter.check:
; CHECK-NEXT:    [[N_VEC_REMAINING:%.*]] = sub i64 1024, [[N_VEC]]
; CHECK-NEXT:    [[MIN_EPILOG_ITERS_CHECK:%.*]] = icmp ult i64 [[N_VEC_REMAINING]], 2
; CHECK-NEXT:    br i1 [[MIN_EPILOG_ITERS_CHECK]], label [[VEC_EPILOG_SCALAR_PH]], label [[VEC_EPILOG_PH]]
; CHECK:       vec.epilog.ph:
; CHECK-NEXT:    [[VEC_EPILOG_RESUME_VAL:%.*]] = phi i64 [ [[N_VEC]], [[VEC_EPILOG_ITER_CHECK]] ], [ 0, [[VECTOR_MAIN_LOOP_ITER_CHECK]] ]
; CHECK-NEXT:    br label [[VEC_EPILOG_VECTOR_BODY:%.*]]
; CHECK:       vec.epilog.vector.body:
; CHECK-NEXT:    [[OFFSET_IDX:%.*]] = phi i64 [ [[VEC_EPILOG_RESUME_VAL]], [[VEC_EPILOG_PH]] ], [ [[INDEX_NEXT3:%.*]], [[VEC_EPILOG_VECTOR_BODY]] ]
; CHECK-NEXT:    [[TMP11:%.*]] = add i64 [[OFFSET_IDX]], 0
; CHECK-NEXT:    [[TMP12:%.*]] = getelementptr inbounds i8, i8* [[A]], i64 [[TMP11]]
; CHECK-NEXT:    [[TMP13:%.*]] = getelementptr inbounds i8, i8* [[TMP12]], i32 0
; CHECK-NEXT:    [[TMP14:%.*]] = bitcast i8* [[TMP13]] to <2 x i8>*
; CHECK-NEXT:    store <2 x i8> <i8 1, i8 1>, <2 x i8>* [[TMP14]], align 1
; CHECK-NEXT:    [[INDEX_NEXT3]] = add nuw i64 [[OFFSET_IDX]], 2
; CHECK-NEXT:    [[TMP15:%.*]] = icmp eq i64 [[INDEX_NEXT3]], 1024
; CHECK-NEXT:    br i1 [[TMP15]], label [[VEC_EPILOG_MIDDLE_BLOCK:%.*]], label [[VEC_EPILOG_VECTOR_BODY]], !llvm.loop [[LOOP2:![0-9]+]]
; CHECK:       vec.epilog.middle.block:
; CHECK-NEXT:    [[CMP_N1:%.*]] = icmp eq i64 1024, 1024
; CHECK-NEXT:    br i1 [[CMP_N1]], label [[EXIT_LOOPEXIT:%.*]], label [[VEC_EPILOG_SCALAR_PH]]
; CHECK:       vec.epilog.scalar.ph:
; CHECK-NEXT:    [[BC_RESUME_VAL:%.*]] = phi i64 [ 1024, [[VEC_EPILOG_MIDDLE_BLOCK]] ], [ [[N_VEC]], [[VEC_EPILOG_ITER_CHECK]] ], [ 0, [[ITER_CHECK:%.*]] ]
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[IV:%.*]] = phi i64 [ [[BC_RESUME_VAL]], [[VEC_EPILOG_SCALAR_PH]] ], [ [[IV_NEXT:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i8, i8* [[A]], i64 [[IV]]
; CHECK-NEXT:    store i8 1, i8* [[ARRAYIDX]], align 1
; CHECK-NEXT:    [[IV_NEXT]] = add nuw nsw i64 [[IV]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp ne i64 [[IV_NEXT]], 1024
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_BODY]], label [[EXIT_LOOPEXIT]], !llvm.loop [[LOOP4:![0-9]+]]
; CHECK:       exit.loopexit:
; CHECK-NEXT:    br label [[EXIT]]
; CHECK:       exit:
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:
  %iv = phi i64 [ 0, %entry ], [ %iv.next, %for.body ]
  %arrayidx = getelementptr inbounds i8, i8* %A, i64 %iv
  store i8 1, i8* %arrayidx, align 1
  %iv.next = add nuw nsw i64 %iv, 1
  %exitcond = icmp ne i64 %iv.next, 1024
  br i1 %exitcond, label %for.body, label %exit, !llvm.loop !0

exit:
  ret void
}

!0 = !{!0, !1}
!1 = !{!"llvm.loop.vectorize.scalable.enable", i1 true}
