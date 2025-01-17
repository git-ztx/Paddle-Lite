set(op_DEPS tensor op op_params)

lite_cc_library(conv_op SRCS conv_op.cc DEPS ${op_DEPS})
lite_cc_library(pool_op SRCS pool_op.cc DEPS ${op_DEPS})
lite_cc_library(fc_op SRCS fc_op.cc DEPS ${op_DEPS})
lite_cc_library(relu_op SRCS relu_op.cc DEPS ${op_DEPS})
lite_cc_library(mul_op SRCS mul_op.cc DEPS ${op_DEPS})
lite_cc_library(scale_op SRCS scale_op.cc DEPS ${op_DEPS})
lite_cc_library(softmax_op SRCS softmax_op.cc DEPS ${op_DEPS})
lite_cc_library(reshape_op SRCS reshape_op.cc DEPS ${op_DEPS} )
lite_cc_library(batch_norm_op SRCS batch_norm_op.cc DEPS ${op_DEPS})
lite_cc_library(feed_op SRCS feed_op.cc DEPS ${op_DEPS})
lite_cc_library(fetch_op SRCS fetch_op.cc DEPS ${op_DEPS})
lite_cc_library(io_copy_op SRCS io_copy_op.cc DEPS ${op_DEPS})
lite_cc_library(io_copy_once_op SRCS io_copy_once_op.cc DEPS io_copy_op ${op_DEPS})
lite_cc_library(activation_ops SRCS activation_ops.cc DEPS ${op_DEPS})
lite_cc_library(elementwise_ops SRCS elementwise_ops.cc DEPS ${op_DEPS})
lite_cc_library(lrn_op_lite SRCS lrn_op.cc DEPS ${op_DEPS})
lite_cc_library(decode_bboxes_op_lite SRCS decode_bboxes_op.cc DEPS ${op_DEPS})
lite_cc_library(box_coder_op_lite SRCS box_coder_op.cc DEPS ${op_DEPS})
lite_cc_library(multiclass_nms_op_lite SRCS multiclass_nms_op.cc DEPS ${op_DEPS})
lite_cc_library(fusion_elementwise_activation_ops SRCS fusion_elementwise_activation_ops.cc DEPS elementwise_ops ${op_DEPS})
lite_cc_library(mean_op SRCS mean_op.cc DEPS ${op_DEPS})
lite_cc_library(fill_constant_op SRCS fill_constant_op.cc DEPS ${op_DEPS})
lite_cc_library(sgd_op SRCS sgd_op.cc DEPS ${op_DEPS})
lite_cc_library(uniform_random_op SRCS uniform_random_op.cc DEPS ${op_DEPS})
lite_cc_library(power_op SRCS power_op.cc DEPS ${op_DEPS})
lite_cc_library(shuffle_channel_op SRCS shuffle_channel_op.cc DEPS ${op_DEPS})
lite_cc_library(yolo_box_op SRCS yolo_box_op.cc DEPS ${op_DEPS})
lite_cc_library(interpolate_op SRCS interpolate_op.cc DEPS ${op_DEPS})
lite_cc_library(argmax_op SRCS argmax_op.cc DEPS ${op_DEPS})
lite_cc_library(axpy_op SRCS axpy_op.cc DEPS ${op_DEPS})
lite_cc_library(gru_unit_op SRCS gru_unit_op.cc DEPS ${op_DEPS})
lite_cc_library(gru_op SRCS gru_op.cc DEPS ${op_DEPS})
lite_cc_library(layout_op SRCS layout_op.cc DEPS ${op_DEPS})
lite_cc_library(layout_once_op SRCS layout_once_op.cc DEPS ${op_DEPS})
lite_cc_library(while_op SRCS while_op.cc DEPS ${op_DEPS})
lite_cc_library(lookup_table_op SRCS lookup_table_op.cc DEPS ${op_DEPS})
lite_cc_library(beam_search_decode_op SRCS beam_search_decode_op.cc DEPS ${op_DEPS})
lite_cc_library(prior_box_op SRCS prior_box_op.cc DEPS ${op_DEPS})
lite_cc_library(density_prior_box_op SRCS density_prior_box_op.cc DEPS ${op_DEPS})

lite_cc_library(op_params SRCS op_params.cc DEPS tensor any)
lite_cc_library(dropout_op SRCS dropout_op.cc DEPS ${op_DEPS})
lite_cc_library(concat_op SRCS concat_op.cc DEPS ${op_DEPS})
lite_cc_library(pad2d_op SRCS pad2d_op.cc DEPS ${op_DEPS})
lite_cc_library(negative_op SRCS negative_op.cc DEPS ${op_DEPS})
lite_cc_library(crop_op SRCS crop_op.cc DEPS ${op_DEPS})
lite_cc_library(calib_op SRCS calib_op.cc DEPS ${op_DEPS})
lite_cc_library(calib_once_op SRCS calib_once_op.cc DEPS ${op_DEPS})
lite_cc_library(split_op SRCS split_op.cc DEPS ${op_DEPS})
lite_cc_library(transpose_op SRCS transpose_op.cc DEPS ${op_DEPS})
lite_cc_library(fake_quant SRCS fake_quantize_moving_avg_max_abs.cc DEPS ${op_DEPS})
lite_cc_library(fake_dequant SRCS fake_dequantize_max_abs.cc DEPS ${op_DEPS})
lite_cc_library(conv_transpose_op SRCS conv_transpose_op.cc DEPS ${op_DEPS})
lite_cc_library(im2sequence_op SRCS im2sequence_op.cc DEPS ${op_DEPS})
lite_cc_library(sequence_softmax_op SRCS sequence_softmax_op.cc DEPS ${op_DEPS})
lite_cc_library(norm_op SRCS norm_op.cc DEPS ${op_DEPS})
lite_cc_library(graph_op SRCS graph_op.cc DEPS ${op_DEPS})
lite_cc_library(topk_op SRCS topk_op.cc DEPS ${op_DEPS})
lite_cc_library(increment_op SRCS increment_op.cc DEPS ${op_DEPS})
lite_cc_library(write_to_array_op SRCS write_to_array_op.cc DEPS ${op_DEPS})
lite_cc_library(graph_op_lite SRCS graph_op.cc DEPS ${op_DEPS})
lite_cc_library(logical_xor  SRCS logical_op.cc DEPS ${op_DEPS})
lite_cc_library(logical_and  SRCS logical_op.cc DEPS ${op_DEPS})
lite_cc_library(logical_or  SRCS logical_op.cc DEPS ${op_DEPS})
lite_cc_library(logical_not  SRCS logical_op.cc DEPS ${op_DEPS})
lite_cc_library(less_than  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(equal  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(not_equal  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(less_equal  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(greater_than  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(greater_equal  SRCS compare_op.cc DEPS ${op_DEPS})
lite_cc_library(read_from_array_op SRCS read_from_array_op.cc DEPS ${op_DEPS})
lite_cc_library(beam_search_op SRCS beam_search_op.cc DEPS ${op_DEPS})
lite_cc_library(sequence_pool_op_lite SRCS sequence_pool_op.cc DEPS ${op_DEPS})
lite_cc_library(sequence_expand_op_lite SRCS sequence_expand_op.cc DEPS ${op_DEPS})
lite_cc_library(reduce_max_op_lite SRCS reduce_max_op.cc DEPS ${op_DEPS})
lite_cc_library(lod_reset_op SRCS lod_reset_op.cc DEPS ${op_DEPS})
lite_cc_library(is_empty SRCS is_empty_op.cc DEPS ${op_DEPS})
lite_cc_library(shape_op_lite SRCS shape_op.cc DEPS ${op_DEPS})
lite_cc_library(cast_op_lite SRCS cast_op.cc DEPS ${op_DEPS})
lite_cc_library(slice_op_lite SRCS slice_op.cc DEPS ${op_DEPS})


set(ops
        conv_op
        pool_op
        fc_op
        relu_op
        mul_op
        scale_op
        softmax_op
        reshape_op
        batch_norm_op
        feed_op
        fetch_op
        gru_unit_op
        gru_op
        beam_search_decode_op
        lookup_table_op
        io_copy_op
        io_copy_once_op
        elementwise_ops
        fusion_elementwise_activation_ops
        lrn_op_lite
	decode_bboxes_op_lite
	multiclass_nms_op_lite
        decode_bboxes_op_lite
        box_coder_op_lite
        multiclass_nms_op_lite
        mean_op
        fill_constant_op
        activation_ops
        dropout_op
        concat_op
        pad2d_op
        crop_op
        prior_box_op
        density_prior_box_op
        negative_op
        calib_op
        calib_once_op
        split_op
        transpose_op
        fake_quant
        fake_dequant
        sgd_op
        uniform_random_op
        power_op
        yolo_box_op
        shuffle_channel_op
        argmax_op
        axpy_op
        conv_transpose_op
        im2sequence_op
        sequence_softmax_op
        norm_op
        layout_op
        layout_once_op
        interpolate_op
        logical_xor
        logical_and        
        logical_or        
        logical_not        
        equal        
        not_equal        
        less_than        
        while_op
        less_equal        
        greater_than        
        greater_equal        
        graph_op
        topk_op
        increment_op
        write_to_array_op
        read_from_array_op
        beam_search_op
        sequence_pool_op_lite
        sequence_expand_op_lite
        reduce_max_op_lite
        lod_reset_op
        is_empty 
        shape_op_lite
        cast_op_lite
        slice_op_lite
        CACHE INTERNAL "ops lite")

if (NOT LITE_WITH_X86)
    lite_cc_test(test_fc_op SRCS fc_op_test.cc
                DEPS fc_op memory
                X86_DEPS fc_compute_x86
                ARM_DEPS fc_compute_arm)
    lite_cc_test(test_pool_op SRCS pool_op_test.cc
                DEPS pool_op memory
                ARM_DEPS pool_compute_arm)
    lite_cc_test(test_scale_op SRCS scale_op_test.cc DEPS scale_op memory)
    lite_cc_test(test_softmax_op SRCS softmax_op_test.cc DEPS softmax_op memory)
    #lite_cc_test(test_reshape_op SRCS reshape_op_test.cc DEPS reshape_op memory)
    lite_cc_test(test_batch_norm_op SRCS batch_norm_op_test.cc DEPS batch_norm_op memory)
    lite_cc_test(test_concat_op SRCS concat_op_test.cc DEPS concat_op memory)
    lite_cc_test(test_calib_op SRCS calib_op_test.cc DEPS calib_op memory ARM_DEPS calib_compute_arm)
    lite_cc_test(test_fusion_elementwise_activation_ops
                SRCS fusion_elementwise_activation_ops_test.cc
                DEPS fusion_elementwise_activation_ops memory)
    lite_cc_test(test_transpose_op SRCS transpose_op_test.cc DEPS transpose_op memory)
endif()
