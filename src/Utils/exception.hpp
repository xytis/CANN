#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <exception>
#include <string>

namespace exception
{

    class kill_event:public std::exception
    {
    public:
        kill_event() throw()
        {

        }
        const char* what() const throw()
        {
            return "The Program Was KILLED, yay";
        }
        ~kill_event () throw () {}
    };

    class SDLException: public std::exception
    {
    public:
        enum SDLExceptionType
        {
            VIDEO   =   0,
            INIT,
            SURFACE,
            TTF,
        };
    private:
        std::string m_reason;
        SDLExceptionType    m_type;
    public:
        SDLException(std::string reason, SDLExceptionType type) throw():
        m_reason(reason),
        m_type(type)
        {
        }
        const char* what() const throw()
        {
            return m_reason.c_str();
        }
        const SDLExceptionType type() const throw()
        {
            return m_type;
        }
        ~SDLException () throw () {}
    };

    class InstanceException: public std::exception
    {
    private:
        std::string m_reason;
    public:
        InstanceException(std::string reason) throw()
        {
            m_reason = reason;
        }
        const char* what() const throw()
        {
            return m_reason.c_str();
        }
        ~InstanceException () throw () {}
    };

    class custom: public std::exception
    {
    private:
        std::string m_reason;
    public:
        custom(std::string reason) throw()
        {
            m_reason = reason;
        }
        const char* what() const throw()
        {
            return m_reason.c_str();
        }
        ~custom () throw () {}
    };

    class Fatal: public std::exception
    {
    private:
        std::string m_reason;
    public:
        Fatal(std::string reason) throw()
        {
            m_reason = reason;
        }
        const char* what() const throw()
        {
            return m_reason.c_str();
        }
        ~Fatal () throw () {}
    };

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
