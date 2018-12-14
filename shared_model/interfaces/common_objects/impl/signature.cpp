/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "interfaces/common_objects/signature.hpp"

#include "cryptography/public_key.hpp"
#include "cryptography/signed.hpp"

namespace shared_model {
  namespace interface {
    bool Signature::operator==(const Signature &rhs) const {
      return publicKey() == rhs.publicKey();
    }

    /// Lexograplic comparison.
    bool Signature::operator<(const Signature &rhs) const {
      return publicKey() < rhs.publicKey()
          or (publicKey() == rhs.publicKey()
              and signedData() < rhs.signedData());
    }

    std::string Signature::toString() const {
      return detail::PrettyStringBuilder()
          .init("Signature")
          .append("publicKey", publicKey().hex())
          .append("signedData", signedData().hex())
          .finalize();
    }
  }  // namespace interface
}  // namespace shared_model
