/* 
 * Modified from
 * 
 * Reference arithmetic coding
 * Copyright (c) Project Nayuki
 * 
 * https://www.nayuki.io/page/reference-arithmetic-coding
 * https://github.com/nayuki/Reference-arithmetic-coding
 */

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include "DhpcModel.hpp"

using std::uint32_t;
using std::vector;


DhpcModel::Context::Context(uint32_t symbols, bool hasSubctx) :
		frequencies(vector<uint32_t>(symbols, 0)) {
	if (hasSubctx) {
		for (uint32_t i = 0; i < symbols; i++)
			subcontexts.push_back(std::unique_ptr<Context>(nullptr));
	}
}


DhpcModel::DhpcModel(int et, int ct, int m, int z) :
		rootContext(std::unique_ptr<Context>(nullptr)),
		// orderMinus1Freqs(FlatFrequencyTable(symbolLimit)),
		extensibility(et), credibility(ct), order(m), node_limit(z) {

	if (order >= 0) {
		rootContext.reset(new Context(symbolLimit, order >= 1));
		rootContext->frequencies.increment(escapeSymbol);
	}
}


void DhpcModel::incrementContexts(const vector<uint32_t> &history, uint32_t symbol) {
	if (history.size() > static_cast<unsigned int>(order) || symbol >= symbolLimit)
		throw std::invalid_argument("Illegal argument");
	
	Context *ctx = rootContext.get();
	ctx->frequencies.increment(symbol);
	std::size_t i = 0;
	for (uint32_t sym : history) {
		vector<std::unique_ptr<Context> > &subctxs = ctx->subcontexts;
		if (subctxs.empty())
			throw std::logic_error("Assertion error");
		
		std::unique_ptr<Context> &subctx = subctxs.at(sym);
		if (subctx.get() == nullptr) {
			subctx.reset(new Context(symbolLimit, i + 1 < static_cast<unsigned int>(order)));
			subctx->frequencies.increment(escapeSymbol);
		}
		ctx = subctx.get();
		ctx->frequencies.increment(symbol);
		i++;
	}
}

void DhpcModel::estimate() {
	
	return;
}

// void DhpcModel::predict() {
// 	return;
// }

// void DhpcModel::update() {
// 	return;
// }