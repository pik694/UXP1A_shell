//
// Created by Daniel Bigos on 12.06.18.
//

#include "Command.h"

using namespace shell::parser::structures;

Command::Command( const std::string &command ) :
    word_( command ),
    isBackground_( false ) { }

std::string Command::getWord()
{
    return word_;
}

std::vector< std::string > &Command::getArguments()
{
    return argumentList_;
}

void Command::addArgument( const std::string &argument )
{
    argumentList_.push_back( argument );
}

std::vector< std::unique_ptr< Redirection > > &Command::getRedirections()
{
    return redirectionList_;
}

void Command::addRedirection( std::unique_ptr< Redirection > &redirection )
{
    redirectionList_.push_back( std::move( redirection ));
}

std::unique_ptr< HereDocument > &Command::getHereDocument()
{
    return hereDocument_;
}

void Command::addHereDocument( std::unique_ptr< HereDocument > &here_document )
{
    hereDocument_ = std::move( here_document );
}

bool Command::getIsBackground()
{
    return isBackground_;
}

void Command::setBackgroundExecution()
{
    isBackground_ = true;
}
