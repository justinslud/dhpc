/* 
 * Reference arithmetic coding
 * Copyright (c) Project Nayuki
 * 
 * https://www.nayuki.io/page/reference-arithmetic-coding
 * https://github.com/nayuki/Reference-arithmetic-coding
 */

#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "FrequencyTable.hpp"


class DhpcModel {
	
	/*---- Helper structure ----*/
	
	public: class Context final {
		
		public: SimpleFrequencyTable frequencies;
		
		public: std::vector<std::unique_ptr<Context> > subcontexts;
		
		public: explicit Context(std::uint32_t symbols, bool hasSubctx);
		
	};
	
	
	
	/*---- Fields ----*/
	
	// public: int modelOrder;
	
	// changed, but don't need more/less?
	private: static const std::uint32_t symbolLimit = 257;
	private: static const std::uint32_t escapeSymbol = 256;

	// can use for history
	public: std::unique_ptr<Context> rootContext;

	public: int extensibility, credibility, order, node_limit;
	
	
	/*---- Constructor ----*/
	
	public: explicit DhpcModel(int et, int ct, int m, int z);
	
	
	/*---- Methods ----*/
	
	public: void incrementContexts(const std::vector<std::uint32_t> &history, std::uint32_t symbol);
	
	
	private: static std::vector<std::uint32_t> makeEmpty(std::uint32_t len);

	private: void estimate();
	
};
