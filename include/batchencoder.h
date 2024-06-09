#pragma once

#include "context.cuh"
#include "ntt.cuh"
#include "plaintext.h"

class PhantomBatchEncoder {

private:

    std::size_t slots_;

    phantom::util::cuda_shared_ptr<uint64_t> matrix_reps_index_map_;

    phantom::util::cuda_shared_ptr<uint64_t> data_;

    void populate_matrix_reps_index_map(const cudaStream_t &stream) const;

public:

    /**
    Creates a BatchEncoder. It is necessary that the encryption parameters
    given through the SEALContext object support batching.

    @param[in] parms The PhantomContext
    @throws std::invalid_argument if the encryption parameters are not valid for batching
    @throws std::invalid_argument if scheme is not scheme_type::bfv
    */
    explicit PhantomBatchEncoder(const PhantomContext &context, const cudaStream_t &stream = nullptr);

    void encode(const PhantomContext &context, const std::vector<uint64_t> &values_matrix, PhantomPlaintext &destination,
                const cudaStream_t &stream = nullptr) const;

    void decode(const PhantomContext &context, const PhantomPlaintext &plain, std::vector<uint64_t> &destination,
                const cudaStream_t &stream = nullptr) const;

    /**
     Returns the number of complex numbers encoded.
     */
    [[nodiscard]] inline std::size_t slot_count() const noexcept {
        return slots_;
    }

    [[nodiscard]] inline uint64_t *matrix_reps_index_map() const noexcept {
        return matrix_reps_index_map_.get();
    }
};
