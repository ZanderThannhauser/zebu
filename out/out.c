
// assigns parser state ids

// assigns tokenizer state ids

// assigns grammar ids

// declares parser start state

// builds tables:
	// (parser state id, ) -> (tokenizer start state id, )
	
	// (tokenizer state id, next char) -> (
		// unaccepting: next tokenizer state id |
		//   accepting: token id)
	
	// (parser state id, token id) -> (
		//  shift: new parser state id |
		// reduce: grammar id)
	
	// (parser state, grammar id) -> new parser state id
	

