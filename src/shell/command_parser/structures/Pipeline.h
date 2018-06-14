//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_PIPELINE_H
#define UXP1A_SHELL_PIPELINE_H

#include <vector>
#include <memory>
#include "AbstractSyntaxTree.hpp"
#include "Command.h"
#include "CommandList.h"

namespace shell::parser::structures
{
    class Pipeline : public AbstractSyntaxTree
    {
    public:
        explicit Pipeline() = default;
        virtual ~Pipeline() = default;

        std::vector< std::unique_ptr< CommandList > > &getCommandsList();
        void addCommandList( std::unique_ptr< CommandList > &command_list );

    private:
        std::vector< std::unique_ptr< CommandList > > commandsList_;
    };

}
#endif //UXP1A_SHELL_PIPELINE_H
