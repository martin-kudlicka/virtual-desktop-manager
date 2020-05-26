#ifndef IAPPLICATIONVIEW_H
#define IAPPLICATIONVIEW_H

EXTERN_C const IID IID_IApplicatonView;

struct IApplicationView : public IUnknown
{
};

_COM_SMARTPTR_TYPEDEF(IApplicationView, IID_IApplicatonView);

#endif