//
//  FirstDataSDK.h
//  SDK
//  Copyright (c) 2018, GeoPagos.
//  All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 */
@interface FirstDataSDK : NSObject

/**
 Callback with results of operations
 
 @param resultInfo Dictionary with the result. It's content depends
 on the performed operation. If `success` = `false`, it may include
 an `error` key value of type `NSError`.
 
 @param success `true` if the operation was successful
 */
typedef void(^FDOperationCompletion)(NSDictionary* _Nullable resultInfo, BOOL success);

/**
 Get an instance of FirstDataSDK.
 */
+ (instancetype) sharedSDK;

/**
 Init FirstDataSDK instance. This method must be called before using the SDK,
 usually in `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]`
 
 @param apiKey The developer apiKey
 */
- (void) startWithAPIKey:(NSString*)apiKey;

/**
 Set de session token assigned to the user. Subsequent operations will use this token.
 
 @param userToken The assigned session token
 */
- (void) setUserToken:(NSString*)userToken;

/**
 Use this method to make a payment.
 
 @param amount Amount to charge in the payment. Must be positive.
 @param description Sale description, shown on the receipt.
 @param tipAmount Tip for this transaction.
 @param viewController `UIViewController` where the payment screen will be shown.
 @param completion Callback called when payment is finished, with a dictionary
 with the result.
 */
- (void) chargeAmount:(CGFloat)amount
          description:(nullable NSString*)description
            tipAmount:(CGFloat)tipAmount
presentFromViewController:(UIViewController *)viewController
           completion:(FDOperationCompletion)completion;

/**
 Use this method to make a payment.
 
 @param amount Amount to charge in the payment. Must be positive.
 @param reference Optional reference number to link with this payment.
 To use in `-[FirstDataSDK retrievePaymentInfoForReference:completion:]`.
 >Must be unique.
 @param description Sale description, shown on the receipt.
 @param tipAmount Tip for this transaction.
 @param viewController `UIViewController` where the payment screen will be shown.
 @param completion Callback called when payment is finished, with a dictionary
 with the result.
 */
- (void) chargeAmount:(CGFloat)amount
            reference:(nullable NSString*)reference
          description:(nullable NSString*)description
            tipAmount:(CGFloat)tipAmount
presentFromViewController:(UIViewController *)viewController
           completion:(FDOperationCompletion)completion;

/**
 Main color for the application.
 */
@property (nonatomic, copy, nonnull) UIColor *mainColor;

/**
 Use this method to send the recepit for an operation id.
 
 @param operationId The operation id returned by this SDK after a successful sale.
 @param email The client's email to send the receipt.
 @param completion Callback to be called on operation end.
 */
- (void) sendReceiptForOperationID:(NSString *)operationId
                           toEmail:(NSString *)email
                        completion:(FDOperationCompletion)completion;

/**
 Use this method to download the pdf of a specific operation id.
 You may use `UIPrintInteractionController` to print it.
 
 @param operationId The operation id returned by this SDK after a successful sale.
 @param completion Callback to be called on operation end, including the receipt
 inside the `receipt` key of the dictionary.
 */
- (void) getPDFReceiptForOperationID:(NSString *)operationId
                         completion:(FDOperationCompletion)completion;

/**
 Use this method to retrieve the payment information associated to an operationId
 
 @param operationId The operationId to retrieve information
 @param completion The callback for this operation
 */
- (void) retrievePaymentInfoForOperationID:(NSString *)operationId
                                completion:(FDOperationCompletion)completion;

/**
 Use this method to retrieve the payment information associated to an reference number
 
 @param reference The reference number to retrieve information
 @param completion The callback for this operation
 */
- (void) retrievePaymentInfoForReference:(NSString *)reference
                              completion:(FDOperationCompletion)completion;

/**
 Use this method to upload a new merchant logo to logged user.
 
 @param image Image to upload.
 @param completion Callback for this operation.
 */
-(void) changeMerchantLogo:(UIImage *)image
                completion:(FDOperationCompletion)completion;

/**
 Use this method to make a refund or annulation for specific operation id.
 
 @param operationId The id of operation to refund.
 @param partialEnabled Indicates if partial amount is enabled. If `true`, the user can enter a custom amount for this refund.
 @param viewController `UIViewController` `UIViewController` where the refund screen will be shown.
 @param completion Callback for this operation.
 */
- (void) refundOperationID:(NSString *)operationId
       enablePartialAmount:(BOOL)partialEnabled
 presentFromViewController:(UIViewController *)viewController
                completion:(FDOperationCompletion)completion;


@end

NS_ASSUME_NONNULL_END

