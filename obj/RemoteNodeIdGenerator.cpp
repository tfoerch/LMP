/*
 * RemoteNodeIdGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"
#include "obj/RemoteNodeIdGenerator_def.hpp"
#include "obj/ObjectHeaderGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::remote_node_id_grammar<BufOutIterType>;
