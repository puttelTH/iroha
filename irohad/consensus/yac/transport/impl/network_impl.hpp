/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_NETWORK_IMPL_HPP
#define IROHA_NETWORK_IMPL_HPP

#include "consensus/yac/transport/yac_network_interface.hpp"  // for YacNetwork
#include "yac.grpc.pb.h"

#include <memory>
#include <unordered_map>

#include "consensus/yac/messages.hpp"
#include "interfaces/common_objects/types.hpp"
#include "logger/logger.hpp"
#include "network/impl/async_grpc_client.hpp"

namespace iroha {
  namespace consensus {
    namespace yac {

      struct CommitMessage;
      struct RejectMessage;
      struct VoteMessage;

      /**
       * Class which provides implementation of transport for consensus based on
       * grpc
       */
      class NetworkImpl : public YacNetwork, public proto::Yac::Service {
       public:
        explicit NetworkImpl(
            std::shared_ptr<network::AsyncGrpcClient<google::protobuf::Empty>>
                async_call);
        void subscribe(
            std::shared_ptr<YacNetworkNotifications> handler) override;

        void sendState(const shared_model::interface::Peer &to,
                       const std::vector<VoteMessage> &state) override;

        /**
         * Receive votes from another peer;
         * Naming is confusing, because this is rpc call that
         * perform on another machine;
         */
        grpc::Status SendState(
            ::grpc::ServerContext *context,
            const ::iroha::consensus::yac::proto::State *request,
            ::google::protobuf::Empty *response) override;

       private:
        /**
         * Create GRPC connection for given peer if it does not exist in
         * peers map
         * @param peer to instantiate connection with
         */
        void createPeerConnection(const shared_model::interface::Peer &peer);

        /**
         * Mapping of peer objects to connections
         */
        std::unordered_map<shared_model::interface::types::AddressType,
                           std::unique_ptr<proto::Yac::StubInterface>>
            peers_;

        /**
         * Subscriber of network messages
         */
        std::weak_ptr<YacNetworkNotifications> handler_;

        /**
         * Rpc call to provide an ability to perform call grpc endpoints
         */
        std::shared_ptr<network::AsyncGrpcClient<google::protobuf::Empty>>
            async_call_;
      };

    }  // namespace yac
  }    // namespace consensus
}  // namespace iroha

#endif  // IROHA_NETWORK_IMPL_HPP
