

// a class by this name also exists in the MxDataService class.
// this is the master class for all codes in the system.
// these are the codes that are populated into the 'SpecificError' property
// on the ArchestrAResult when the ErrorCode property is set to 'SpecificError'
public ref class StatusCodes
{
public:
    /// <summary>
    /// The operation completed successfully.
    /// </summary>
    static const unsigned int Good = 0x00000000;

    /// <summary>
    /// The operation completed however its outputs may not be usable.
    /// </summary>
    static const unsigned int Uncertain = 0x40000000;

    /// <summary>
    /// The operation failed.
    /// </summary>
    static const unsigned int Bad = 0x80000000;

    /// <summary>
    /// An unexpected error occurred.
    /// </summary>
    static const unsigned int BadUnexpectedError = 0x80010000;

    /// <summary>
    /// An internal error occurred as a result of a programming or configuration error.
    /// </summary>
    static const unsigned int BadInternalError = 0x80020000;

    /// <summary>
    /// Not enough memory to complete the operation.
    /// </summary>
    static const unsigned int BadOutOfMemory = 0x80030000;

    /// <summary>
    /// An operating system resource is not available.
    /// </summary>
    static const unsigned int BadResourceUnavailable = 0x80040000;

    /// <summary>
    /// A low level communication error occurred.
    /// </summary>
    static const unsigned int BadCommunicationError = 0x80050000;

    /// <summary>
    /// Encoding halted because of invalid data in the objects being serialized.
    /// </summary>
    static const unsigned int BadEncodingError = 0x80060000;

    /// <summary>
    /// Decoding halted because of invalid data in the stream.
    /// </summary>
    static const unsigned int BadDecodingError = 0x80070000;

    /// <summary>
    /// The message encoding/decoding limits imposed by the stack have been exceeded.
    /// </summary>
    static const unsigned int BadEncodingLimitsExceeded = 0x80080000;

    /// <summary>
    /// The request message size exceeds limits set by the server.
    /// </summary>
    static const unsigned int BadRequestTooLarge = 0x80B80000;

    /// <summary>
    /// The response message size exceeds limits set by the client.
    /// </summary>
    static const unsigned int BadResponseTooLarge = 0x80B90000;

    /// <summary>
    /// An unrecognized response was received from the server.
    /// </summary>
    static const unsigned int BadUnknownResponse = 0x80090000;

    /// <summary>
    /// The operation timed out.
    /// </summary>
    static const unsigned int BadTimeout = 0x800A0000;

    /// <summary>
    /// The server does not support the requested service.
    /// </summary>
    static const unsigned int BadServiceUnsupported = 0x800B0000;

    /// <summary>
    /// The operation was cancelled because the application is shutting down.
    /// </summary>
    static const unsigned int BadShutdown = 0x800C0000;

    /// <summary>
    /// The operation could not complete because the client is not connected to the server.
    /// </summary>
    static const unsigned int BadServerNotConnected = 0x800D0000;

    /// <summary>
    /// The server has stopped and cannot process any requests.
    /// </summary>
    static const unsigned int BadServerHalted = 0x800E0000;

    /// <summary>
    /// There was nothing to do because the client passed a list of operations with no elements.
    /// </summary>
    static const unsigned int BadNothingToDo = 0x800F0000;

    /// <summary>
    /// The request could not be processed because it specified too many operations.
    /// </summary>
    static const unsigned int BadTooManyOperations = 0x80100000;

    /// <summary>
    /// The extension object cannot be (de)serialized because the data type id is not recognized.
    /// </summary>
    static const unsigned int BadDataTypeIdUnknown = 0x80110000;

    /// <summary>
    /// The certificate provided as a parameter is not valid.
    /// </summary>
    static const unsigned int BadCertificateInvalid = 0x80120000;

    /// <summary>
    /// An error occurred verifying security.
    /// </summary>
    static const unsigned int BadSecurityChecksFailed = 0x80130000;

    /// <summary>
    /// The Certificate has expired or is not yet valid.
    /// </summary>
    static const unsigned int BadCertificateTimeInvalid = 0x80140000;

    /// <summary>
    /// An Issuer Certificate has expired or is not yet valid.
    /// </summary>
    static const unsigned int BadCertificateIssuerTimeInvalid = 0x80150000;

    /// <summary>
    /// The HostName used to connect to a Server does not match a HostName in the Certificate.
    /// </summary>
    static const unsigned int BadCertificateHostNameInvalid = 0x80160000;

    /// <summary>
    /// The URI specified in the ApplicationDescription does not match the URI in the Certificate.
    /// </summary>
    static const unsigned int BadCertificateUriInvalid = 0x80170000;

    /// <summary>
    /// The Certificate may not be used for the requested operation.
    /// </summary>
    static const unsigned int BadCertificateUseNotAllowed = 0x80180000;

    /// <summary>
    /// The Issuer Certificate may not be used for the requested operation.
    /// </summary>
    static const unsigned int BadCertificateIssuerUseNotAllowed = 0x80190000;

    /// <summary>
    /// The Certificate is not trusted.
    /// </summary>
    static const unsigned int BadCertificateUntrusted = 0x801A0000;

    /// <summary>
    /// It was not possible to determine if the Certificate has been revoked.
    /// </summary>
    static const unsigned int BadCertificateRevocationUnknown = 0x801B0000;

    /// <summary>
    /// It was not possible to determine if the Issuer Certificate has been revoked.
    /// </summary>
    static const unsigned int BadCertificateIssuerRevocationUnknown = 0x801C0000;

    /// <summary>
    /// The Certificate has been revoked.
    /// </summary>
    static const unsigned int BadCertificateRevoked = 0x801D0000;

    /// <summary>
    /// The Issuer Certificate has been revoked.
    /// </summary>
    static const unsigned int BadCertificateIssuerRevoked = 0x801E0000;

    /// <summary>
    /// User does not have permission to perform the requested operation.
    /// </summary>
    static const unsigned int BadUserAccessDenied = 0x801F0000;

    /// <summary>
    /// The user identity token is not valid.
    /// </summary>
    static const unsigned int BadIdentityTokenInvalid = 0x80200000;

    /// <summary>
    /// The user identity token is valid but the server has rejected it.
    /// </summary>
    static const unsigned int BadIdentityTokenRejected = 0x80210000;

    /// <summary>
    /// The specified secure channel is not longer valid.
    /// </summary>
    static const unsigned int BadSecureChannelIdInvalid = 0x80220000;

    /// <summary>
    /// The timestamp is outside the range allowed by the server.
    /// </summary>
    static const unsigned int BadInvalidTimestamp = 0x80230000;

    /// <summary>
    /// The nonce does appear to be not a random value or it is not the correct length.
    /// </summary>
    static const unsigned int BadNonceInvalid = 0x80240000;

    /// <summary>
    /// The session id is not valid.
    /// </summary>
    static const unsigned int BadSessionIdInvalid = 0x80250000;

    /// <summary>
    /// The session was closed by the client.
    /// </summary>
    static const unsigned int BadSessionClosed = 0x80260000;

    /// <summary>
    /// The session cannot be used because ActivateSession has not been called.
    /// </summary>
    static const unsigned int BadSessionNotActivated = 0x80270000;

    /// <summary>
    /// The subscription id is not valid.
    /// </summary>
    static const unsigned int BadSubscriptionIdInvalid = 0x80280000;

    /// <summary>
    /// The header for the request is missing or invalid.
    /// </summary>
    static const unsigned int BadRequestHeaderInvalid = 0x802A0000;

    /// <summary>
    /// The timestamps to return parameter is invalid.
    /// </summary>
    static const unsigned int BadTimestampsToReturnInvalid = 0x802B0000;

    /// <summary>
    /// The request was cancelled by the client.
    /// </summary>
    static const unsigned int BadRequestCanceledByClient = 0x802C0000;

    /// <summary>
    /// The subscription was transferred to another session.
    /// </summary>
    static const unsigned int GoodSubscriptionTransferred = 0x002D0000;

    /// <summary>
    /// The processing will complete asynchronously.
    /// </summary>
    static const unsigned int GoodCompletesAsynchronously = 0x002E0000;

    /// <summary>
    /// Sampling has slowed down due to resource limitations.
    /// </summary>
    static const unsigned int GoodOverload = 0x002F0000;

    /// <summary>
    /// The value written was accepted but was clamped.
    /// </summary>
    static const unsigned int GoodClamped = 0x00300000;

    /// <summary>
    /// Communication with the data source is defined, but not established, and there is no last known value available.
    /// </summary>
    static const unsigned int BadNoCommunication = 0x80310000;

    /// <summary>
    /// Waiting for the server to obtain values from the underlying data source.
    /// </summary>
    static const unsigned int BadWaitingForInitialData = 0x80320000;

    /// <summary>
    /// The syntax of the node id is not valid.
    /// </summary>
    static const unsigned int BadNodeIdInvalid = 0x80330000;

    /// <summary>
    /// The node id refers to a node that does not exist in the server address space.
    /// </summary>
    static const unsigned int BadNodeIdUnknown = 0x80340000;

    /// <summary>
    /// The attribute is not supported for the specified Node.
    /// </summary>
    static const unsigned int BadAttributeIdInvalid = 0x80350000;

    /// <summary>
    /// The syntax of the index range parameter is invalid.
    /// </summary>
    static const unsigned int BadIndexRangeInvalid = 0x80360000;

    /// <summary>
    /// No data exists within the range of indexes specified.
    /// </summary>
    static const unsigned int BadIndexRangeNoData = 0x80370000;

    /// <summary>
    /// The data encoding is invalid.
    /// </summary>
    static const unsigned int BadDataEncodingInvalid = 0x80380000;

    /// <summary>
    /// The server does not support the requested data encoding for the node.
    /// </summary>
    static const unsigned int BadDataEncodingUnsupported = 0x80390000;

    /// <summary>
    /// The access level does not allow reading or subscribing to the Node.
    /// </summary>
    static const unsigned int BadNotReadable = 0x803A0000;

    /// <summary>
    /// The access level does not allow writing to the Node.
    /// </summary>
    static const unsigned int BadNotWritable = 0x803B0000;

    /// <summary>
    /// The value was out of range.
    /// </summary>
    static const unsigned int BadOutOfRange = 0x803C0000;

    /// <summary>
    /// The requested operation is not supported.
    /// </summary>
    static const unsigned int BadNotSupported = 0x803D0000;

    /// <summary>
    /// A requested item was not found or a search operation ended without success.
    /// </summary>
    static const unsigned int BadNotFound = 0x803E0000;

    /// <summary>
    /// The object cannot be used because it has been deleted.
    /// </summary>
    static const unsigned int BadObjectDeleted = 0x803F0000;

    /// <summary>
    /// Requested operation is not implemented.
    /// </summary>
    static const unsigned int BadNotImplemented = 0x80400000;

    /// <summary>
    /// The monitoring mode is invalid.
    /// </summary>
    static const unsigned int BadMonitoringModeInvalid = 0x80410000;

    /// <summary>
    /// The monitoring item id does not refer to a valid monitored item.
    /// </summary>
    static const unsigned int BadMonitoredItemIdInvalid = 0x80420000;

    /// <summary>
    /// The monitored item filter parameter is not valid.
    /// </summary>
    static const unsigned int BadMonitoredItemFilterInvalid = 0x80430000;

    /// <summary>
    /// The server does not support the requested monitored item filter.
    /// </summary>
    static const unsigned int BadMonitoredItemFilterUnsupported = 0x80440000;

    /// <summary>
    /// A monitoring filter cannot be used in combination with the attribute specified.
    /// </summary>
    static const unsigned int BadFilterNotAllowed = 0x80450000;

    /// <summary>
    /// A mandatory structured parameter was missing or null.
    /// </summary>
    static const unsigned int BadStructureMissing = 0x80460000;

    /// <summary>
    /// The event filter is not valid.
    /// </summary>
    static const unsigned int BadEventFilterInvalid = 0x80470000;

    /// <summary>
    /// The content filter is not valid.
    /// </summary>
    static const unsigned int BadContentFilterInvalid = 0x80480000;

    /// <summary>
    /// An unregognized operator was provided in a filter.
    /// </summary>
    static const unsigned int BadFilterOperatorInvalid = 0x80C10000;

    /// <summary>
    /// A valid operator was provided, but the server does not provide support for this filter operator.
    /// </summary>
    static const unsigned int BadFilterOperatorUnsupported = 0x80C20000;

    /// <summary>
    /// The number of operands provided for the filter operator was less then expected for the operand provided.
    /// </summary>
    static const unsigned int BadFilterOperandCountMismatch = 0x80C30000;

    /// <summary>
    /// The operand used in a content filter is not valid.
    /// </summary>
    static const unsigned int BadFilterOperandInvalid = 0x80490000;

    /// <summary>
    /// The referenced element is not a valid element in the content filter.
    /// </summary>
    static const unsigned int BadFilterElementInvalid = 0x80C40000;

    /// <summary>
    /// The referenced literal is not a valid value.
    /// </summary>
    static const unsigned int BadFilterLiteralInvalid = 0x80C50000;

    /// <summary>
    /// The continuation point provide is longer valid.
    /// </summary>
    static const unsigned int BadContinuationPointInvalid = 0x804A0000;

    /// <summary>
    /// The operation could not be processed because all continuation points have been allocated.
    /// </summary>
    static const unsigned int BadNoContinuationPoints = 0x804B0000;

    /// <summary>
    /// The operation could not be processed because all continuation points have been allocated.
    /// </summary>
    static const unsigned int BadReferenceTypeIdInvalid = 0x804C0000;

    /// <summary>
    /// The browse direction is not valid.
    /// </summary>
    static const unsigned int BadBrowseDirectionInvalid = 0x804D0000;

    /// <summary>
    /// The node is not part of the view.
    /// </summary>
    static const unsigned int BadNodeNotInView = 0x804E0000;

    /// <summary>
    /// The ServerUri is not a valid URI.
    /// </summary>
    static const unsigned int BadServerUriInvalid = 0x804F0000;

    /// <summary>
    /// No ServerName was specified.
    /// </summary>
    static const unsigned int BadServerNameMissing = 0x80500000;

    /// <summary>
    /// No DiscoveryUrl was specified.
    /// </summary>
    static const unsigned int BadDiscoveryUrlMissing = 0x80510000;

    /// <summary>
    /// The semaphore file specified by the client is not valid.
    /// </summary>
    static const unsigned int BadSemaphoreFileMissing = 0x80520000;

    /// <summary>
    /// The security token request type is not valid.
    /// </summary>
    static const unsigned int BadRequestTypeInvalid = 0x80530000;

    /// <summary>
    /// The security mode does not meet the requirements set by the Server.
    /// </summary>
    static const unsigned int BadSecurityModeRejected = 0x80540000;

    /// <summary>
    /// The security policy does not meet the requirements set by the Server.
    /// </summary>
    static const unsigned int BadSecurityPolicyRejected = 0x80550000;

    /// <summary>
    /// The server has reached its maximum number of sessions.
    /// </summary>
    static const unsigned int BadTooManySessions = 0x80560000;

    /// <summary>
    /// The user token signature is missing or invalid.
    /// </summary>
    static const unsigned int BadUserSignatureInvalid = 0x80570000;

    /// <summary>
    /// The signature generated with the client certificate is missing or invalid.
    /// </summary>
    static const unsigned int BadApplicationSignatureInvalid = 0x80580000;

    /// <summary>
    /// The client did not provide at least one software certificate that is valid and meets the profile requirements for the server.
    /// </summary>
    static const unsigned int BadNoValidCertificates = 0x80590000;

    /// <summary>
    /// The Server does not support changing the user identity assigned to the session.
    /// </summary>
    static const unsigned int BadIdentityChangeNotSupported = 0x80C60000;

    /// <summary>
    /// The request was cancelled by the client with the Cancel service.
    /// </summary>
    static const unsigned int BadRequestCanceledByRequest = 0x805A0000;

    /// <summary>
    /// The parent node id does not to refer to a valid node.
    /// </summary>
    static const unsigned int BadParentNodeIdInvalid = 0x805B0000;

    /// <summary>
    /// The reference could not be created because it violates constraints imposed by the data model.
    /// </summary>
    static const unsigned int BadReferenceNotAllowed = 0x805C0000;

    /// <summary>
    /// The requested node id was reject because it was either invalid or server does not allow node ids to be specified by the client.
    /// </summary>
    static const unsigned int BadNodeIdRejected = 0x805D0000;

    /// <summary>
    /// The requested node id is already used by another node.
    /// </summary>
    static const unsigned int BadNodeIdExists = 0x805E0000;

    /// <summary>
    /// The node class is not valid.
    /// </summary>
    static const unsigned int BadNodeClassInvalid = 0x805F0000;

    /// <summary>
    /// The browse name is invalid.
    /// </summary>
    static const unsigned int BadBrowseNameInvalid = 0x80600000;

    /// <summary>
    /// The browse name is not unique among nodes that share the same relationship with the parent.
    /// </summary>
    static const unsigned int BadBrowseNameDuplicated = 0x80610000;

    /// <summary>
    /// The node attributes are not valid for the node class.
    /// </summary>
    static const unsigned int BadNodeAttributesInvalid = 0x80620000;

    /// <summary>
    /// The type definition node id does not reference an appropriate type node.
    /// </summary>
    static const unsigned int BadTypeDefinitionInvalid = 0x80630000;

    /// <summary>
    /// The source node id does reference a valid node.
    /// </summary>
    static const unsigned int BadSourceNodeIdInvalid = 0x80640000;

    /// <summary>
    /// The target node id does reference a valid node.
    /// </summary>
    static const unsigned int BadTargetNodeIdInvalid = 0x80650000;

    /// <summary>
    /// The reference type between the nodes is already defined.
    /// </summary>
    static const unsigned int BadDuplicateReferenceNotAllowed = 0x80660000;

    /// <summary>
    /// The server does not allow this type of self reference on this node.
    /// </summary>
    static const unsigned int BadInvalidSelfReference = 0x80670000;

    /// <summary>
    /// The reference type is not valid for a reference to a remote server.
    /// </summary>
    static const unsigned int BadReferenceLocalOnly = 0x80680000;

    /// <summary>
    /// The server will not allow the node to be deleted.
    /// </summary>
    static const unsigned int BadNoDeleteRights = 0x80690000;

    /// <summary>
    /// The server was not able to delete all target references.
    /// </summary>
    static const unsigned int UncertainReferenceNotDeleted = 0x40BC0000;

    /// <summary>
    /// The server index is not valid.
    /// </summary>
    static const unsigned int BadServerIndexInvalid = 0x806A0000;

    /// <summary>
    /// The view id does not refer to a valid view node.
    /// </summary>
    static const unsigned int BadViewIdUnknown = 0x806B0000;

    /// <summary>
    /// The view timestamp is not available or not supported.
    /// </summary>
    static const unsigned int BadViewTimestampInvalid = 0x80C90000;

    /// <summary>
    /// The view parameters are not consistent withe each other.
    /// </summary>
    static const unsigned int BadViewParameterMismatch = 0x80CA0000;

    /// <summary>
    /// The view version is not available or not supported.
    /// </summary>
    static const unsigned int BadViewVersionInvalid = 0x80CB0000;

    /// <summary>
    /// The list of references may not be complete because the underlying system is not available.
    /// </summary>
    static const unsigned int UncertainNotAllNodesAvailable = 0x40C00000;

    /// <summary>
    /// The server should have followed a reference to a node in a remote server but did not. The result set may be incomplete.
    /// </summary>
    static const unsigned int GoodResultsMayBeIncomplete = 0x00BA0000;

    /// <summary>
    /// The provided Nodeid was not a type definition nodeid.
    /// </summary>
    static const unsigned int BadNotTypeDefinition = 0x80C80000;

    /// <summary>
    /// One of the references to follow in the relative path references to a node in the address space in another server.
    /// </summary>
    static const unsigned int UncertainReferenceOutOfServer = 0x406C0000;

    /// <summary>
    /// The requested operation has too many matches to return.
    /// </summary>
    static const unsigned int BadTooManyMatches = 0x806D0000;

    /// <summary>
    /// The requested operation requires too many resources in the server.
    /// </summary>
    static const unsigned int BadQueryTooComplex = 0x806E0000;

    /// <summary>
    /// The requested operation has no match to return.
    /// </summary>
    static const unsigned int BadNoMatch = 0x806F0000;

    /// <summary>
    /// The max age parameter is invalid.
    /// </summary>
    static const unsigned int BadMaxAgeInvalid = 0x80700000;

    /// <summary>
    /// The history details parameter is not valid.
    /// </summary>
    static const unsigned int BadHistoryOperationInvalid = 0x80710000;

    /// <summary>
    /// The server does not support the requested operation.
    /// </summary>
    static const unsigned int BadHistoryOperationUnsupported = 0x80720000;

    /// <summary>
    /// The defined timestamp to return was invalid.
    /// </summary>
    static const unsigned int BadInvalidTimestampArgument = 0x80BD0000;

    /// <summary>
    /// The server does support writing the combination of value, status and timestamps provided.
    /// </summary>
    static const unsigned int BadWriteNotSupported = 0x80730000;

    /// <summary>
    /// The value supplied for the attribute is not of the same type as the attribute's value.
    /// </summary>
    static const unsigned int BadTypeMismatch = 0x80740000;

    /// <summary>
    /// The method id does not refer to a method for the specified object.
    /// </summary>
    static const unsigned int BadMethodInvalid = 0x80750000;

    /// <summary>
    /// The client did not specify all of the input arguments for the method.
    /// </summary>
    static const unsigned int BadArgumentsMissing = 0x80760000;

    /// <summary>
    /// The server has reached its  maximum number of subscriptions.
    /// </summary>
    static const unsigned int BadTooManySubscriptions = 0x80770000;

    /// <summary>
    /// The server has reached the maximum number of queued publish requests.
    /// </summary>
    static const unsigned int BadTooManyPublishRequests = 0x80780000;

    /// <summary>
    /// There is no subscription available for this session.
    /// </summary>
    static const unsigned int BadNoSubscription = 0x80790000;

    /// <summary>
    /// The sequence number is unknown to the server.
    /// </summary>
    static const unsigned int BadSequenceNumberUnknown = 0x807A0000;

    /// <summary>
    /// The requested notification message is no longer available.
    /// </summary>
    static const unsigned int BadMessageNotAvailable = 0x807B0000;

    /// <summary>
    /// The Client of the current Session does not support one or more Profiles that are necessary for the Subscription.
    /// </summary>
    static const unsigned int BadInsufficientClientProfile = 0x807C0000;

    /// <summary>
    /// The sub-state machine is not currently active.
    /// </summary>
    static const unsigned int BadStateNotActive = 0x80BF0000;

    /// <summary>
    /// The server cannot process the request because it is too busy.
    /// </summary>
    static const unsigned int BadTcpServerTooBusy = 0x807D0000;

    /// <summary>
    /// The type of the message specified in the header invalid.
    /// </summary>
    static const unsigned int BadTcpMessageTypeInvalid = 0x807E0000;

    /// <summary>
    /// The SecureChannelId and/or TokenId are not currently in use.
    /// </summary>
    static const unsigned int BadTcpSecureChannelUnknown = 0x807F0000;

    /// <summary>
    /// The size of the message specified in the header is too large.
    /// </summary>
    static const unsigned int BadTcpMessageTooLarge = 0x80800000;

    /// <summary>
    /// There are not enough resources to process the request.
    /// </summary>
    static const unsigned int BadTcpNotEnoughResources = 0x80810000;

    /// <summary>
    /// An internal error occurred.
    /// </summary>
    static const unsigned int BadTcpInternalError = 0x80820000;

    /// <summary>
    /// The Server does not recognize the QueryString specified.
    /// </summary>
    static const unsigned int BadTcpEndpointUrlInvalid = 0x80830000;

    /// <summary>
    /// The request could not be sent because of a network interruption.
    /// </summary>
    static const unsigned int BadRequestInterrupted = 0x80840000;

    /// <summary>
    /// Timeout occurred while processing the request.
    /// </summary>
    static const unsigned int BadRequestTimeout = 0x80850000;

    /// <summary>
    /// The secure channel has been closed.
    /// </summary>
    static const unsigned int BadSecureChannelClosed = 0x80860000;

    /// <summary>
    /// The token has expired or is not recognized.
    /// </summary>
    static const unsigned int BadSecureChannelTokenUnknown = 0x80870000;

    /// <summary>
    /// The sequence number is not valid.
    /// </summary>
    static const unsigned int BadSequenceNumberInvalid = 0x80880000;

    /// <summary>
    /// The applications do not have compatible protocol versions.
    /// </summary>
    static const unsigned int BadProtocolVersionUnsupported = 0x80BE0000;

    /// <summary>
    /// There is a problem with the configuration that affects the usefulness of the value.
    /// </summary>
    static const unsigned int BadConfigurationError = 0x80890000;

    /// <summary>
    /// The variable should receive its value from another variable, but has never been configured to do so.
    /// </summary>
    static const unsigned int BadNotConnected = 0x808A0000;

    /// <summary>
    /// There has been a failure in the device/data source that generates the value that has affected the value.
    /// </summary>
    static const unsigned int BadDeviceFailure = 0x808B0000;

    /// <summary>
    /// There has been a failure in the sensor from which the value is derived by the device/data source.
    /// </summary>
    static const unsigned int BadSensorFailure = 0x808C0000;

    /// <summary>
    /// The source of the data is not operational.
    /// </summary>
    static const unsigned int BadOutOfService = 0x808D0000;

    /// <summary>
    /// The deadband filter is not valid.
    /// </summary>
    static const unsigned int BadDeadbandFilterInvalid = 0x808E0000;

    /// <summary>
    /// Communication to the data source has failed. The variable value is the last value that had a good quality.
    /// </summary>
    static const unsigned int UncertainNoCommunicationLastUsableValue = 0x408F0000;

    /// <summary>
    /// Whatever was updating this value has stopped doing so.
    /// </summary>
    static const unsigned int UncertainLastUsableValue = 0x40900000;

    /// <summary>
    /// The value is an operational value that was manually overwritten.
    /// </summary>
    static const unsigned int UncertainSubstituteValue = 0x40910000;

    /// <summary>
    /// The value is an initial value for a variable that normally receives its value from another variable.
    /// </summary>
    static const unsigned int UncertainInitialValue = 0x40920000;

    /// <summary>
    /// The value is at one of the sensor limits.
    /// </summary>
    static const unsigned int UncertainSensorNotAccurate = 0x40930000;

    /// <summary>
    /// The value is outside of the range of values defined for this parameter.
    /// </summary>
    static const unsigned int UncertainEngineeringUnitsExceeded = 0x40940000;

    /// <summary>
    /// The value is derived from multiple sources and has less than the required number of Good sources.
    /// </summary>
    static const unsigned int UncertainSubNormal = 0x40950000;

    /// <summary>
    /// The value has been overridden.
    /// </summary>
    static const unsigned int GoodLocalOverride = 0x00960000;

    /// <summary>
    /// This Condition refresh failed, a Condition refresh operation is already in progress.
    /// </summary>
    static const unsigned int BadRefreshInProgress = 0x80970000;

    /// <summary>
    /// This condition has already been disabled.
    /// </summary>
    static const unsigned int BadConditionAlreadyDisabled = 0x80980000;

    /// <summary>
    /// This condition has already been enabled.
    /// </summary>
    static const unsigned int BadConditionAlreadyEnabled = 0x80CC0000;

    /// <summary>
    /// Property not available, this condition is disabled.
    /// </summary>
    static const unsigned int BadConditionDisabled = 0x80990000;

    /// <summary>
    /// The specified event id if not recognized.
    /// </summary>
    static const unsigned int BadEventIdUnknown = 0x809A0000;

    /// <summary>
    /// The event cannot be acknowledged.
    /// </summary>
    static const unsigned int BadEventNotAcknowledgeable = 0x80BB0000;

    /// <summary>
    /// The dialog condition is not active.
    /// </summary>
    static const unsigned int BadDialogNotActive = 0x80CD0000;

    /// <summary>
    /// The response is not valid for the dialog.
    /// </summary>
    static const unsigned int BadDialogResponseInvalid = 0x80CE0000;

    /// <summary>
    /// The condition branch has already been acknowledged.
    /// </summary>
    static const unsigned int BadConditionBranchAlreadyAcked = 0x80CF0000;

    /// <summary>
    /// The condition branch has already been confirmed.
    /// </summary>
    static const unsigned int BadConditionBranchAlreadyConfirmed = 0x80D00000;

    /// <summary>
    /// The condition has already been shelved.
    /// </summary>
    static const unsigned int BadConditionAlreadyShelved = 0x80D10000;

    /// <summary>
    /// The condition is not currently shelved.
    /// </summary>
    static const unsigned int BadConditionNotShelved = 0x80D20000;

    /// <summary>
    /// The shelving time not within an acceptable range.
    /// </summary>
    static const unsigned int BadShelvingTimeoutOfRange = 0x80D30000;

    /// <summary>
    /// No data exists for the requested time range or event filter.
    /// </summary>
    static const unsigned int BadNoData = 0x809B0000;

    /// <summary>
    /// No data found to provide upper or lower bound value.
    /// </summary>
    static const unsigned int BadBoundNotFound = 0x80D70000;

    /// <summary>
    /// The server cannot retrieve a bound for the variable.
    /// </summary>
    static const unsigned int BadBoundNotSupported = 0x80D80000;

    /// <summary>
    /// Data is missing due to collection started/stopped/lost.
    /// </summary>
    static const unsigned int BadDataLost = 0x809D0000;

    /// <summary>
    /// Expected data is unavailable for the requested time range due to an un-mounted volume, an off-line archive or tape, or similar reason for temporary unavailability.
    /// </summary>
    static const unsigned int BadDataUnavailable = 0x809E0000;

    /// <summary>
    /// The data or event was not successfully inserted because a matching entry exists.
    /// </summary>
    static const unsigned int BadEntryExists = 0x809F0000;

    /// <summary>
    /// The data or event was not successfully updated because no matching entry exists.
    /// </summary>
    static const unsigned int BadNoEntryExists = 0x80A00000;

    /// <summary>
    /// The client requested history using a timestamp format the server does not support (i.e requested ServerTimestamp when server only supports SourceTimestamp).
    /// </summary>
    static const unsigned int BadTimestampNotSupported = 0x80A10000;

    /// <summary>
    /// The data or event was successfully inserted into the historical database.
    /// </summary>
    static const unsigned int GoodEntryInserted = 0x00A20000;

    /// <summary>
    /// The data or event field was successfully replaced in the historical database.
    /// </summary>
    static const unsigned int GoodEntryReplaced = 0x00A30000;

    /// <summary>
    /// The value is derived from multiple values and has less than the required number of Good values.
    /// </summary>
    static const unsigned int UncertainDataSubNormal = 0x40A40000;

    /// <summary>
    /// No data exists for the requested time range or event filter.
    /// </summary>
    static const unsigned int GoodNoData = 0x00A50000;

    /// <summary>
    /// The data or event field was successfully replaced in the historical database.
    /// </summary>
    static const unsigned int GoodMoreData = 0x00A60000;

    /// <summary>
    /// The requested number of Aggregates does not match the requested number of NodeIds.
    /// </summary>
    static const unsigned int BadAggregateListMismatch = 0x80D40000;

    /// <summary>
    /// The requested Aggregate is not support by the server.
    /// </summary>
    static const unsigned int BadAggregateNotSupported = 0x80D50000;

    /// <summary>
    /// The aggregate value could not be derived due to invalid data inputs.
    /// </summary>
    static const unsigned int BadAggregateInvalidInputs = 0x80D60000;

    /// <summary>
    /// The communication layer has raised an event.
    /// </summary>
    static const unsigned int GoodCommunicationEvent = 0x00A70000;

    /// <summary>
    /// The system is shutting down.
    /// </summary>
    static const unsigned int GoodShutdownEvent = 0x00A80000;

    /// <summary>
    /// The operation is not finished and needs to be called again.
    /// </summary>
    static const unsigned int GoodCallAgain = 0x00A90000;

    /// <summary>
    /// A non-critical timeout occurred.
    /// </summary>
    static const unsigned int GoodNonCriticalTimeout = 0x00AA0000;

    /// <summary>
    /// One or more arguments are invalid.
    /// </summary>
    static const unsigned int BadInvalidArgument = 0x80AB0000;

    /// <summary>
    /// Could not establish a network connection to remote server.
    /// </summary>
    static const unsigned int BadConnectionRejected = 0x80AC0000;

    /// <summary>
    /// The server has disconnected from the client.
    /// </summary>
    static const unsigned int BadDisconnect = 0x80AD0000;

    /// <summary>
    /// The network connection has been closed.
    /// </summary>
    static const unsigned int BadConnectionClosed = 0x80AE0000;

    /// <summary>
    /// The operation cannot be completed because the object is closed, uninitialized or in some other invalid state.
    /// </summary>
    static const unsigned int BadInvalidState = 0x80AF0000;

    /// <summary>
    /// Cannot move beyond end of the stream.
    /// </summary>
    static const unsigned int BadEndOfStream = 0x80B00000;

    /// <summary>
    /// No data is currently available for reading from a non-blocking stream.
    /// </summary>
    static const unsigned int BadNoDataAvailable = 0x80B10000;

    /// <summary>
    /// The asynchronous operation is waiting for a response.
    /// </summary>
    static const unsigned int BadWaitingForResponse = 0x80B20000;

    /// <summary>
    /// The asynchronous operation was abandoned by the caller.
    /// </summary>
    static const unsigned int BadOperationAbandoned = 0x80B30000;

    /// <summary>
    /// The stream did not return all data requested (possibly because it is a non-blocking stream).
    /// </summary>
    static const unsigned int BadExpectedStreamToBlock = 0x80B40000;

    /// <summary>
    /// Non blocking behaviour is required and the operation would block.
    /// </summary>
    static const unsigned int BadWouldBlock = 0x80B50000;

    /// <summary>
    /// A value had an invalid syntax.
    /// </summary>
    static const unsigned int BadSyntaxError = 0x80B60000;

    /// <summary>
    /// The operation could not be finished because all available connections are in use.
    /// </summary>
    static const unsigned int BadMaxConnectionsReached = 0x80B70000;
};
