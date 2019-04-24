//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// speech_api_factory.h: Implementation declarations for CSpxSpeechApiFactory C++ class
//

#pragma once
#include <spxdebug.h>
#include <spxerror.h>
#include "service_helpers.h"
#include "interface_helpers.h"
#include "property_bag_impl.h"


namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {


class CSpxSpeechApiFactory :
    public ISpxObjectWithSiteInitImpl<ISpxGenericSite>,
    public ISpxServiceProvider,
    public ISpxSpeechApiFactory,
    public ISpxGenericSite,
    public ISpxPropertyBagImpl
{
public:

    // debugging to make sure CSpxSpeechApiFactory is released.
#if _DEBUG
    ~ CSpxSpeechApiFactory()
    {
        SPX_DBG_TRACE_SCOPE(__FUNCTION__, __FUNCTION__);
    }
#endif

    SPX_INTERFACE_MAP_BEGIN()
        SPX_INTERFACE_MAP_ENTRY(ISpxInterfaceBase)
        SPX_INTERFACE_MAP_ENTRY(ISpxObjectWithSite)
        SPX_INTERFACE_MAP_ENTRY(ISpxObjectInit)
        SPX_INTERFACE_MAP_ENTRY(ISpxServiceProvider)
        SPX_INTERFACE_MAP_ENTRY(ISpxSpeechApiFactory)
        SPX_INTERFACE_MAP_ENTRY(ISpxGenericSite)
        SPX_INTERFACE_MAP_ENTRY(ISpxNamedProperties)
    SPX_INTERFACE_MAP_END()

    // --- ISpxSpeechApiFactory
    std::shared_ptr<ISpxRecognizer> CreateSpeechRecognizerFromConfig(const char* pszLanguage, OutputFormat format, std::shared_ptr<ISpxAudioConfig> audioInput) override;
    std::shared_ptr<ISpxSpeechBotConnector> CreateSpeechBotConnectorFromConfig(const char* pszLanguage, OutputFormat format, std::shared_ptr<ISpxAudioConfig> audioInput) override;
    std::shared_ptr<ISpxRecognizer> CreateIntentRecognizerFromConfig(const char* pszLanguage, OutputFormat format, std::shared_ptr<ISpxAudioConfig> audioInput) override;
    std::shared_ptr<ISpxRecognizer> CreateTranslationRecognizerFromConfig(const std::string& sourcelanguage, const std::vector<std::string>& targetLanguages, const std::string& voice, std::shared_ptr<ISpxAudioConfig> audioInput) override;

    // --- IServiceProvider
    SPX_SERVICE_MAP_BEGIN()
    SPX_SERVICE_MAP_ENTRY(ISpxNamedProperties)
    SPX_SERVICE_MAP_ENTRY_SITE(GetSite())
    SPX_SERVICE_MAP_END()

protected:

    std::shared_ptr<ISpxNamedProperties> GetParentProperties() const override { return SpxQueryService<ISpxNamedProperties>(GetSite()); }

private:

    std::shared_ptr<ISpxRecognizer> CreateRecognizerFromConfigInternal(
        const char* sessionClassName,
        const char* recognizerClassName,
        const char* language = nullptr,
        OutputFormat format = OutputFormat::Simple,
        std::shared_ptr<ISpxAudioConfig> audioInput = nullptr);

    std::shared_ptr<ISpxRecognizer> CreateTranslationRecognizerFromConfigInternal(
        const std::string& sourceLanguage,
        const std::vector<std::string>& targetLanguages,
        const std::string& voice,
        std::shared_ptr<ISpxAudioConfig> audioInput);

    void InitSessionFromAudioInputConfig(std::shared_ptr<ISpxSession> session, std::shared_ptr<ISpxAudioConfig> audioInput);

    void SetRecognizerProperties(const std::shared_ptr<ISpxNamedProperties>& namedProperties, const char* language, OutputFormat format);
    void SetTranslationProperties(const std::shared_ptr<ISpxNamedProperties>& namedProperties, const std::string& sourceLanguage, const std::vector<std::string>& targetLanguages, const std::string& voice);
};


} } } } // Microsoft::CognitiveServices::Speech::Impl