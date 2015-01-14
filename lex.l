whitespaces [ \t\n]+

%%

[\/][\*][^\*]*([\*]([^\/\*][^\*]*)?)*[\*][\/] {std::cout<<"Comment: "<<matched()<<std::endl;}
whitespaces {std::cout<<"Whitespaces: "<<matched()<<std::endl;}
. {std::cout<<"Others: "<<matched()<<std::endl;}
