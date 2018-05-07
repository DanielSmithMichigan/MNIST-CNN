#include "Layer.h"
#include "Volume4d.h"
using namespace std;

class FullyConnected : public Layer{
	private:
		int nodeCount;
	protected:
	public:
		FullyConnected(int nodeCount, Layer *priorLayer);
		~FullyConnected();
		void feedForward();
		void feedBackward();
		Volume4d *weights;
		Volume *biases;
};