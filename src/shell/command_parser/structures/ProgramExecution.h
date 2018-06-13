//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_PROGRAMEXECUTION_H
#define UXP1A_SHELL_PROGRAMEXECUTION_H

#include <memory>
#include "AbstractSyntaxTree.hpp"
#include "Out.h"
#include "Err.h"
#include "InRedirection.h"
#include "OutRedirection.h"
#include "ErrRedirection.h"

namespace shell::parser::structures
{
    class ProgramExecution : public AbstractSyntaxTree
    {
    public:
        explicit ProgramExecution();
        virtual ~ProgramExecution() = default;

        Out *getOutRedirection();
        Err *getErrRedirection();
        InRedirection *getInRedirection();

        void addInRedirection( std::unique_ptr< InRedirection > & );
        void addOutRedirection( std::unique_ptr< OutRedirection > & );
        void addErrRedirection( std::unique_ptr< ErrRedirection > & );
    private:
        std::unique_ptr< Out > outRedirection_;
        std::unique_ptr< Err > errRedirection_;
        std::unique_ptr< InRedirection > inRedirection_;
    };
}
#endif //UXP1A_SHELL_PROGRAMEXECUTION_H
