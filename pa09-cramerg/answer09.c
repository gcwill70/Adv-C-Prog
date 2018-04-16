#include "answer09.h"

bool isCircular(const node_t * head)
{
	if(head == NULL) {return false;}
	node_t* slow = (node_t*) head;
	node_t* fast = head->next;
	if(fast == NULL) {return false;}

	bool half_freq = true;

	while((fast!=NULL)&&(fast!=slow))
	{
		half_freq = !half_freq;
		if(half_freq)
		{
			slow = slow->next;
		}
		fast = fast->next;
	}
	if(fast == slow) {return true;}
	return false;	
}
