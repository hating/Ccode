	double 	P_each[4]={0},P_all[4]={0};
	for(int loop=0;loop<4;loop++)
	{

		AAA Ahead,*Atemp=NULL;
		
	//Initiation
		Ahead.next=NULL;
		Ahead.Yes=0;
		Ahead.No=0;
		strcpy(Ahead.att,"\0");
	
		for(NodeSample *iter=head->next;iter!=NULL;iter=iter->next)
		{
			int dataCnt=0;
			if(Atemp=find(iter->sample.item[loop],&Ahead))
			{
					if(!strcmp(iter->sample.playTennis,"Yes"))
					{
						Atemp->Yes++;
					}
					if(!strcmp(iter->sample.playTennis,"No"))
					{
						Atemp->No++;
					}
			}
			else
			{
					Atemp=addNodeAAA(&Ahead,iter->sample.item[loop]);
	
					if(!strcmp(iter->sample.playTennis,"Yes"))
					{
						Atemp->Yes++;
					}
					if(!strcmp(iter->sample.playTennis,"No"))
					{
						Atemp->No++;
					}
				
			}
			dataCnt++;
		}
	//Test the read result
		
		for(AAA *iter_print=Ahead.next;iter_print!=NULL;iter_print=iter_print->next)
		{
			printf("attribute:%s\nYes:%d\nNo:%d\n",iter_print->att,iter_print->Yes,iter_print->No);
		}
		
		for(AAA *iter_calc=Ahead.next;iter_calc!=NULL;iter_calc=iter_calc->next)
		{
			P_each[loop]-=iter_calc->Yes* lg2( 1.0*iter_calc->Yes/(iter_calc->Yes+iter_calc->No) ) + iter_calc->No *lg2( 1.0*iter_calc->No/(iter_calc->Yes+iter_calc->No) );
		}
	}
	
	
	for(int i=0;i<4;i++)
	{
		P_each[i]/=14;
		printf("%f\n",P_each[i]);
	}

