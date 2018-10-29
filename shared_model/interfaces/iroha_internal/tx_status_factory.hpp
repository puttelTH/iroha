/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IROHA_TX_STATUS_FACTORY_HPP
#define IROHA_TX_STATUS_FACTORY_HPP

#include <memory>

#include "interfaces/transaction_responses/tx_response.hpp"

namespace shared_model {
  namespace interface {

    /**
     * Factory which creates transaction status response
     */
    class TxStatusFactory {
     public:
      /// return type of all generative methods
      using FactoryReturnType = std::unique_ptr<TransactionResponse>;

      /// type of transaction hash
      using TransactionHashType =
          const TransactionResponse::TransactionHashType &;

      /**
       * value type of the error message which is attached to \class
       * TransactionResponse instance
       */
      using ErrorMessageValueType = TransactionResponse::ErrorMessageType;

      /// const ref of \refitem ErrorMessageValueType
      using ConstRefErrorMessage = const ErrorMessageValueType &;

      /// Pointer to factory method for status creation
      using TxStatusFactoryInvoker = FactoryReturnType (TxStatusFactory::*)(
          TransactionHashType, ConstRefErrorMessage);

      /**
       * @return default value for empty error message
       */
      static ErrorMessageValueType emptyErrorMessage() {
        return {};
      }

      // ------------------------| Stateless statuses |-------------------------

      /// Creates stateless failed transaction status
      virtual FactoryReturnType makeStatelessFail(TransactionHashType,
                                                  ConstRefErrorMessage) = 0;

      /// Creates stateless valid transaction status
      virtual FactoryReturnType makeStatelessValid(TransactionHashType,
                                                   ConstRefErrorMessage) = 0;

      // ------------------------| Stateful statuses |--------------------------

      /// Creates stateful failed transaction status
      virtual FactoryReturnType makeStatefulFail(TransactionHashType,
                                                 ConstRefErrorMessage) = 0;
      /// Creates stateful valid transaction status
      virtual FactoryReturnType makeStatefulValid(TransactionHashType,
                                                  ConstRefErrorMessage) = 0;

      // --------------------------| Final statuses |---------------------------

      /// Creates committed transaction status
      virtual FactoryReturnType makeCommitted(TransactionHashType,
                                              ConstRefErrorMessage) = 0;

      /// Creates rejected transaction status
      virtual FactoryReturnType makeRejected(TransactionHashType,
                                             ConstRefErrorMessage) = 0;

      // --------------------------| Rest statuses |----------------------------

      /// Creates transaction expired status
      virtual FactoryReturnType makeMstExpired(TransactionHashType,
                                               ConstRefErrorMessage) = 0;

      /// Creates transaction is not received status
      virtual FactoryReturnType makeNotReceived(TransactionHashType,
                                                ConstRefErrorMessage) = 0;

      /// Creates status which shows that enough signatures were collected
      virtual FactoryReturnType makeEnoughSignaturesCollected(
          TransactionHashType, ConstRefErrorMessage) = 0;

      /// Creates status which shows that transaction is
      virtual FactoryReturnType makeMstPending(TransactionHashType,
                                               ConstRefErrorMessage) = 0;

      virtual ~TxStatusFactory() = default;
    };
  }  // namespace interface
}  // namespace shared_model

#endif  // IROHA_TX_STATUS_FACTORY_HPP
