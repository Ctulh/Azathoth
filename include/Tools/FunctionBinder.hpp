//
// Created by egor on 2/13/22.
//

#ifndef AZATHOTH_FUNCTIONBINDER_HPP
#define AZATHOTH_FUNCTIONBINDER_HPP

#define BIND_EVENT_FN(className,x) std::bind(&className::x, this, std::placeholders::_1)

#endif //AZATHOTH_FUNCTIONBINDER_HPP
