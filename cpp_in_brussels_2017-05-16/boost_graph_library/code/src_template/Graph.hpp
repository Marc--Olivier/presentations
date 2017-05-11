#pragma once

#include <boost/graph/adjacency_list.hpp>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
	boost::no_property, boost::property<boost::edge_weight_t, float>>;
