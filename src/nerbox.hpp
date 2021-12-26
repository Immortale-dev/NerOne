#ifndef NN_NERBOX
#define NN_NERBOX

#include "nerhelp.hpp"

namespace nerone {
	
	template<typename M, typename T>
	class NerBox {
		// TODO
		// M - mutliplier class
		// T - teacher class
		
		public:
			NerBox();
			~NerBox();
			NerBox(ner_cluster_t cluster);
			
			ner_cluster_t get_cluster();
			void set_cluster(ner_cluster_t cluster);
			
			values_t question(values_t questions); // - processes all the vertices and returns the result
			void correct(values_t answers); // - back propagate all the vertices with current sums
			void teach(values_t questions, values_t answers); // question and correct
			
		protected:
			virtual void propagate();
			virtual void back_propagate();
		
		private:
			ner_cluster_t cluster;
	}
	
}

#endif // NN_NERBOX
