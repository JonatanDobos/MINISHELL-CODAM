probably malloc token elements instead of re-using line_elements (because free) (OR move line_elements_head to first unadopted element node after each token assignation)