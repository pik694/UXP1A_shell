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
#include "HereDocument.h"
#include <vector>
#include <memory>

namespace shell::parser::structures
{
    class Command
    {
    public:
        explicit Command( const std::string &command );
        virtual ~Command() = default;

        std::string getWord();

        std::vector< std::string > &getArguments();
        void addArgument( const std::string &argument );

        std::vector< std::unique_ptr< Redirection > > &getRedirections();
        void addRedirection( std::unique_ptr< Redirection > &redirection );

        std::unique_ptr< HereDocument > &getHereDocument();
        void addHereDocument( std::unique_ptr< HereDocument > &here_document );

        bool getIsBackground();
        void setBackgroundExecution();

     private:
        bool isBackground_ ;
        std::string word_;
        std::vector< std::string > argumentList_;
        std::vector< std::unique_ptr< Redirection > > redirectionList_;
        std::unique_ptr< HereDocument > hereDocument_;
    };
}
#endif //UXP1A_SHELL_PROGRAMEXECUTION_H
