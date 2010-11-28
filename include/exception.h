#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <exception>
#include <string>

namespace exception
{
    class NetworksIncompatible: public std::exception
    {
        private:
            std::string m_reason;
        public:
            NetworksIncompatible(std::string reason) throw()
            {
                m_reason = reason;
            }
            const char* what() const throw()
            {
                return m_reason.c_str();
            }
            ~NetworksIncompatible () throw () {}
    };

    class IDmissmatch: public std::exception
    {
        private:
            std::string m_reason;
        public:
            IDmissmatch(std::string reason) throw()
            {
                m_reason = reason;
            }
            const char* what() const throw()
            {
                return m_reason.c_str();
            }
            ~IDmissmatch () throw () {}
    };

};

#endif // EXCEPTION_H_INCLUDED
