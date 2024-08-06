probably malloc token elements instead of re-using line_elements (because free) (OR move line_elements_head to first unadopted element node after each token assignation)

>> issue: expandables
try the following commands in order:
+	export KEY=value0
+	export $KEY=value1
+	$value0
--
probably due to finding the KEY (value0=value1) in envp[][] as value (KEY=value0) before the KEY() itself
	could be fixed by only allowing capital KEYs and lowercase values?