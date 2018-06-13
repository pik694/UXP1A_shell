//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_ARGUMENT_H
#define UXP1A_SHELL_ARGUMENT_H

namespace shell::parser::structures
{
    class Argument
    {
    public:
        explicit Argument() = default;
        virtual ~Argument() = default;
    };

}
#endif //UXP1A_SHELL_ARGUMENT_H
