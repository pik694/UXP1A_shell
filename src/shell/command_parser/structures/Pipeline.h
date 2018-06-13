//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_PIPELINE_H
#define UXP1A_SHELL_PIPELINE_H

#include <list>
#include <memory>
#include "AbstractSyntaxTree.hpp"
#include "Command.h"

namespace shell::parser::structures
{
    class Pipeline : public AbstractSyntaxTree
    {
    public:
        explicit Pipeline() = default;
        virtual ~Pipeline() = default;

        std::list< std::unique_ptr< Command > > &getCommands();
        void addCommand( std::unique_ptr< Command > & );
    private:
        std::list< std::unique_ptr< Command > > commands_;
    };

}
#endif //UXP1A_SHELL_PIPELINE_H
