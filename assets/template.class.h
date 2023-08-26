#ifndef {}
#define {}

<<<for $NAMESPACES {=(namespace $_ {)}>>>

class <<<=$NAME if $INHERIT {: =$INHERIT_METHOD} =$INHERIT_CLASS>>> {
    public:
        <<<=$NAME>>>() = default;
        <<<~=$NAME>>>() = default;
};

<<<for $NAMESPACES =(})>>>

#endif {}

