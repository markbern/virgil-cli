/**
 * Copyright (C) 2015-2016 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <cli/command/KeygenCommand.h>

#include <cli/api/api.h>
#include <cli/io/Logger.h>
#include <cli/argument/ArgumentParseOptions.h>

using namespace cli;
using cli::command::KeygenCommand;
using cli::argument::ArgumentSource;
using cli::argument::ArgumentParseOptions;
using cli::argument::ArgumentImportance;

using namespace virgil::crypto;

const char* KeygenCommand::doGetName() const {
    return arg::value::VIRGIL_COMMAND_KEYGEN;
}

const char* KeygenCommand::doGetUsage() const {
    return usage::VIRGIL_KEYGEN;
}

ArgumentParseOptions KeygenCommand::doGetArgumentParseOptions() const {
    return ArgumentParseOptions().disableOptionsFirst();
}

void KeygenCommand::doProcess() const {
    ULOG1(INFO) << "Read arguments.";
    auto keyAlgorithm = getArgumentIO()->getKeyAlgorithm(ArgumentImportance::Required);
    auto keyPasswordImportance = getArgumentIO()->hasNoPassword() ?
                                 ArgumentImportance::Optional : ArgumentImportance::Required;
    auto keyPassword = getArgumentIO()->getKeyPassword(keyPasswordImportance);

    ULOG1(INFO)  << "Generate private key.";
    VirgilKeyPair keyPair = VirgilKeyPair::generate(keyAlgorithm, keyPassword.bytesValue());
    ULOG1(INFO)  << "Write private key to the output.";
    getArgumentIO()->getOutputSink(ArgumentImportance::Optional).write(keyPair.privateKey());
}
