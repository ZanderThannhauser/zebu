
#define lambda_helper(c, type, args, exp) ({ \
		type __lambda_##_cc args { \
			return (exp); \
		}; \
		__lambda_##_cc; \
	})

#define lambda(type, args, exp) lambda_helper(COUNTER, type, args, exp)


